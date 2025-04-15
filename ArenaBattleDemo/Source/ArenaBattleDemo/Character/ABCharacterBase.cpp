// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ABCharacterBase.h"
#include "ABCharacterControlData.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AABCharacterBase::AABCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> ShoulderDataRef(TEXT("/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(
			ECharacterControlType::Shoulder,
			ShoulderDataRef.Object
		);
	}

	static ConstructorHelpers::FObjectFinder<UABCharacterControlData> QuarterDataRef(TEXT("/Game/ArenaBattle/CharacterControl/ABC_Quarter.ABC_Quarter"));
	if (QuarterDataRef.Object)
	{
		CharacterControlManager.Add(
			ECharacterControlType::Quarter,
			QuarterDataRef.Object
		);
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

void AABCharacterBase::ProcessComboCommand()
{
	// 현재 재생 중인 콤보 확인.
	if (CurrentCombo == 0)
	{
		// 콤보 액션 시작 처리 후 종료.
		ComboActionBegin();
		return;
	}

	// 콤보가 진행 중일 때는 해당 프레임에 맞는 타이머를 활용.

	// 콤보 타이머 핸들이 유효하지 않다면,
	// 이미 콤보 발동이 걸렸거나 타이밍을 놓친 경우.
	// 이 때는 콤보 처리가 필요하지 않음.
	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
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
	if (AnimInstance)
	{
		const float AttackSpeedRate = 1.f;
		AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

		//몽타주 재생이 시작되면, 재생이 종료될 때 호출되는 델리게이트 등록.
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);
	}
}

//공격 끝났다 함수 - 바인딩된 함수, 4개
void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	//유효성 검사 //꺼지면 안되서, check 말고, ensure
	ensure(CurrentCombo != 0);

	//콤보 초기화
	CurrentCombo = 0;

	//캐릭터 무브먼트 컴포넌트 모드 복구
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}