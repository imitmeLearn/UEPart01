﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ABCharacterBase.h"
#include "ABCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ABComboActionData.h"
#include "Physics/ABCollision.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_ABCAPSULE);		//컴포넌트 설정. 물리에서 만든 매크로 CPROFILE_ABCAPSULE
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));	//메시의 콜리전은 NOCollision 설정 (주로 렉돌에 사용됨).

	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder"));
	if(ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(
			ECharacterControlType::Shoulder,
			ShoulderDataRef.Object
		);
	}

	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuarterDataRef(TEXT("/Game/ArenaBattle/CharacterControl/ABC_Quarter.ABC_Quarter"));
	if(QuarterDataRef.Object)
	{
		CharacterControlManager.Add(
			ECharacterControlType::Quarter,
			QuarterDataRef.Object
		);
	}

	//콤보 액션 몽타주 에셋 설정.
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Game/ArenaBattle/Animation/AM_ComboAttack.AM_ComboAttack"));
	if(ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	//콤보 액션 데이터 에셋 설정.
	static ConstructorHelpers::FObjectFinder<UABComboActionData> ComboActionDataRef(TEXT("/Game/ArenaBattle/ComboAction/ABA_ComboAction.ABA_ComboAction"));
	if(ComboActionDataRef.Object)
	{
		ComboActionData = ComboActionDataRef.Object;
	}
	//죽음 몽타주 에셋 설정
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Game/ArenaBattle/Animation/AM_Dead.AM_Dead"));
	if(DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}
}

void AABCharacterBase::SetCharacterControlData(const UABCharacterControlData* InCharacterControlData)
{
	// Pawn.
	bUseControllerRotationYaw = InCharacterControlData->bUseControllerRotationYaw;

	// CharacterMovement.
	GetCharacterMovement()->bOrientRotationToMovement = InCharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = InCharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = InCharacterControlData->RotationRate;
}

void AABCharacterBase::AttackHitCheck()
{
	UE_LOG(LogTemp,Log,TEXT("HIT!!"));
	////충돌시작지점 계싼
	//캐릭터 몸통에서 약간 앞으로 (캡슐의 반지름 만큼) 설정.
	FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();

	const float AttackRange = 150.f;	//공격거리
	FVector End = Start + GetActorForwardVector() * AttackRange;

	FCollisionQueryParams Params(
		SCENE_QUERY_STAT(Attack)		// SCENE_QUERY_STAT: 언리얼에서 지원하는 분석 툴에 태그를 추가.
		,false							// 두번째 인자: 복잡한 형태의 충돌체를 감지할 지 여부.
		,this							// 세번째 인자: 무시할 액터 목록.
	);

	const float AttackRadius = 30.f;	//트레이스에 사용할 구체의 반지름

	FHitResult OutHitResult;	//트레이스를 호라용해 충돌 검사

	bool HitDetected =
		GetWorld()->SweepSingleByChannel(
			OutHitResult
			,Start
			,End
			,FQuat::Identity
			,CCHANNEL_ABACTION
			,FCollisionShape::MakeSphere(AttackRadius)
			,Params
		);

	///충돌 감지된 경우의 처리.
	if(HitDetected)
	{
		const float AttackDamage = 30.f;	//데미지 양
		FDamageEvent DamageEvent;	//데이미 이벤트

		//데미지 전달
		OutHitResult.GetActor()->TakeDamage(
			AttackDamage
			,DamageEvent
			,GetController()
			,this
		);
	}

	////충돌 디버그 (시각적으로 확인할 수 있도록)
	#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;	//캡슐의 중심 위치.
	float CapsuleHalfHeight = AttackRange * 0.5f;			//캡슐 높이 절반 값
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;	//표시할 색상(안 맞으면 - 빨강, 맞았으면 -초록)'
	DrawDebugCapsule(
		GetWorld()
		,CapsuleOrigin
		,CapsuleHalfHeight
		,AttackRadius
		,FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat()
		,DrawColor
		,false
		,5.f
	);																//캡슐 그리기

	#endif // ENABLE_DRAW_DEBUG
}

float AABCharacterBase::TakeDamage(float DamageAmount,FDamageEvent const & DamageEvent,AController * EventInstigator,AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);

	SetDead();
	return DamageAmount;
}

void AABCharacterBase::ProcessComboCommand()
{
	// 현재 재생 중인 콤보 확인.
	if(CurrentCombo == 0)
	{
		// 콤보 액션 시작 처리 후 종료.
		ComboActionBegin();
		return;
	}

	// 콤보가 진행 중일 때는 해당 프레임에 맞는 타이머를 활용.

	// 콤보 타이머 핸들이 유효하지 않다면,
	// 이미 콤보 발동이 걸렸거나 타이밍을 놓친 경우.
	// 이 때는 콤보 처리가 필요하지 않음.
	if(!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	} else
	{
		HasNextComboCommand = true;
	}
}

void AABCharacterBase::ComboActionBegin()
{
	//콤보 상태를 1로 설정.
	CurrentCombo = 1;

	//이동 비활성화
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	//몽타주 재생.
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance)
	{
		const float AttackSpeedRate = 1.f;
		AnimInstance->Montage_Play(ComboActionMontage,AttackSpeedRate);

		//몽타주 재생이 시작되면, 재생이 종료될 때 호출되는 델리게이트 등록.
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this,&AABCharacterBase::ComboActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate,ComboActionMontage);

		//콤보 확인을 위한 타이머 설정.
		ComboTimerHandle.Invalidate();
		SetComboCheckTimer();
	}
}

//공격 끝났다 함수 - 바인딩된 함수, 4개
void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage,bool IsProperlyEnded)
{
	//유효성 검사 //꺼지면 안되서, check 말고, ensure
	ensure(CurrentCombo != 0);

	//콤보 초기화
	CurrentCombo = 0;

	//캐릭터 무브먼트 컴포넌트 모드 복구
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AABCharacterBase::SetComboCheckTimer()
{
	//현재 재생중인 콤보 인덱스
	int32 ComboIndex = CurrentCombo - 1;

	//콤보 인덱스 값 검증
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	//콤보 시간 계산(확인)
	const float AttackSpeedRate = 1.f;
	float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

	//타이머 설정
	if(ComboEffectiveTime > 0.f)
	{
		//타이머 설정
		GetWorld()->GetTimerManager().SetTimer(
			ComboTimerHandle					//1.설정할 타이머 핸들
			,this								//2.타이머에 설정한 시간이 모두 지냈을 떄, 실행될 함수의 주인.
			,&AABCharacterBase::ComboCheck	//3.타이머에 연동해 실행할 함수 포인터.
			,ComboEffectiveTime				//4.타이머 시간
			,false								//5. 반복여부
		);
	}
}

void AABCharacterBase::ComboCheck()
{
	//타이머 핸들 무효화(초기화).
	ComboTimerHandle.Invalidate();

	//이전 공격 입력이 들어왔는지 확인.
	if(HasNextComboCommand)
	{
		//몽타주 점프 처리.
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if(AnimInstance)
		{
			CurrentCombo = FMath::Clamp(
				CurrentCombo + 1
				,1
				,ComboActionData->MaxComboCount
			);

			//점프할 섹션의 이름 설정(예: ComboAttack2)
			FName NextSection = *FString::Printf(
				TEXT("%s%d")
				,*ComboActionData->MontageSectionNamePrefix		//접두어? - 데이터 에셋 설정에 들어있음.
				,CurrentCombo									//바뀌는 값.
			);
			//섹션 점프
			AnimInstance->Montage_JumpToSection(NextSection,ComboActionMontage);

			//다음 콤보 공격을 위한 타이머 설정.
			SetComboCheckTimer();

			//콤보 공격 입력 플래그 초기화
			HasNextComboCommand = false;
		}
	}
}

void AABCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);	//캐릭터 무브먼트 컴포넌트 끄기
	SetActorEnableCollision(false);										//콜리전 끄기
	PlayDeadAnimation();												//죽는 애니메이션 재생
}

void AABCharacterBase::PlayDeadAnimation()
{
	////몽타주 재생!
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance)
	{
		AnimInstance->StopAllMontages(0.f);	//이미 재생 중인 몽타주가 있따면, 모두 종료.

		const float PlayRate = 1.0f;
		AnimInstance->Montage_Play(DeadMontage,PlayRate);	// 죽음 몽타주 재생.
	}
}