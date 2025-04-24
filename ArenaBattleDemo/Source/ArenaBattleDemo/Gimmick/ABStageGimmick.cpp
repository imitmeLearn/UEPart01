﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Gimmick/ABStageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Physics/ABCollision.h"
#include "Character/ABCharacterNonPlayer.h"

#include "Item/ABItemBox.h" //reward 상자 사용을 위한,해더에서 전방선언했기에!
// Sets default values
AABStageGimmick::AABStageGimmick()
{
	////STAGE SECTION
	Stage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stage"));
	RootComponent = Stage;

	//리소스 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StageMeshRef(TEXT("/Game/ArenaBattle/Environment/Stages/SM_SQUARE.SM_SQUARE"));
	if(StageMeshRef.Object)
	{
		Stage ->SetStaticMesh(StageMeshRef.Object);
	}

	StageTrigger =  CreateDefaultSubobject<UBoxComponent>(TEXT("StageTrigger"));
	StageTrigger -> SetBoxExtent(FVector(775.f,775.f,300.f));
	StageTrigger -> SetupAttachment(Stage);
	StageTrigger -> SetRelativeLocation(FVector(0.f,0.f,250.f));
	StageTrigger -> SetCollisionProfileName(CPROFILE_ABTRIGGER);
	StageTrigger -> OnComponentBeginOverlap.AddDynamic(this,&AABStageGimmick::OnStageTriggerBeginOverlap);

	////GATE SETCION
	static FName GateSockets[] = {
		TEXT("+XGate")
		,TEXT("-XGate")
		,TEXT("+YGate")
		,TEXT("-YGate")
	};

	//리소스 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMeshRef(TEXT("/Game/ArenaBattle/Environment/Props/SM_GATE.SM_GATE"));

	//게이트 생성
	for(const FName& GateSocket : GateSockets)
	{
		//컴포넌트 생성
		UStaticMeshComponent* Gate = CreateDefaultSubobject<UStaticMeshComponent>(GateSocket);

		//셍성한 스테틱 매시 컴포넌트 에셋 설정
		if(GateMeshRef.Object)
		{
			Gate->SetStaticMesh(GateMeshRef.Object);
		}

		//컴포넌트 설정.
		Gate->SetupAttachment(Stage,GateSocket);			//부모 설정
		Gate->SetRelativeLocation(FVector(0.f,-80.f,0.f));	//위치 설정
		Gate->SetRelativeRotation(FRotator(0.f,-90.f,0.f));	//회전 설정

		//생성한 컴포넌트 맵에 추가
		Gates.Add(GateSocket,Gate);

		//문마다 배치할 BoxComponent 생성 및 설정.
		FName TriggerName = *GateSocket.ToString().Append("Trigger");

		//컴포넌트 생성.
		UBoxComponent* GateTrigger = CreateDefaultSubobject<UBoxComponent>(TriggerName);

		// 컴포넌트 설정.
		GateTrigger->SetBoxExtent(FVector(100.0f,100.0f,300.0f));
		GateTrigger->SetupAttachment(Stage,GateSocket);
		GateTrigger->SetRelativeLocation(FVector(70.0f,0.0f,250.0f));
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
		GateTrigger->OnComponentBeginOverlap.AddDynamic(this,&AABStageGimmick::OnGateTriggerBeginOverlap);

		// 태그 설정.
		GateTrigger->ComponentTags.Add(GateSocket);

		//생성한 컴포넌트 배열에 추가.
		GateTriggers.Add(GateTrigger);
	}

	//시작할 때는 준비 상태로 설정.
	CurrentState = EStageState::Ready;

	//열거형 - 델리게이트 맵 설정
	StageChangedActions.Add(
		EStageState::Ready
		//,FOnStageChangedDelegateWrapper(FOnStageChangedDelegate::CreateUObject(this,&AABStageGimmick::SetReady))	//FOnStageChangedDelegateWrapper 생략가능.
		,FOnStageChangedDelegate::CreateUObject(this,&AABStageGimmick::SetReady)

	);

	StageChangedActions.Add(
		EStageState::Fight
		,FOnStageChangedDelegate::CreateUObject(this,&AABStageGimmick::SetFight)
	);

	StageChangedActions.Add(
		EStageState::Reward
		,FOnStageChangedDelegate::CreateUObject(this,&AABStageGimmick::SetChooseReward)
	);

	StageChangedActions.Add(
		EStageState::Next
		,FOnStageChangedDelegate::CreateUObject(this,&AABStageGimmick::SetChooseNext)
	);

	////FIGHT SECTION
	OpponentSpawnTime = 2.f;

	//생성할 NPC 클래스 타입지정
	OpponentClass = AABCharacterNonPlayer::StaticClass();

	////REWARD SETCTION
	//생성할 아이템 상자의 클래스 타입 설정
	RewardItemClass = AABItemBox::StaticClass();

	//생성 위치 설정.
	for(const FName& GateSocket:GateSockets)
	{
		// 소켓 위치를 사용해 위치 값 구하기.
		FVector BoxLocation = Stage->GetSocketLocation(GateSocket) / 2;

		// 맵에 추가.
		RewardBoxLocations.Add(GateSocket,BoxLocation);
	}
}

void AABStageGimmick::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//OnConstruction 이 호출될 때, 상태값도 갱신되도록 처리.
	SetState(CurrentState);
}

void AABStageGimmick::SetState(EStageState InNewState)
{
	//예외처리
	if(CurrentState == InNewState)
	{
		return;
	}
	//현재 상태 업데이트
	CurrentState = InNewState;

	//전달된 상태에 맵에 포함되어 있으면, 델리게이트 실행.
	if(StageChangedActions.Contains(InNewState))	//키 가지고 있으면,
	{
		StageChangedActions[CurrentState].StageChangedDelegate.ExecuteIfBound();
	}
}

void AABStageGimmick::OnStageTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent,AActor * OtherActor,UPrimitiveComponent * OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepResult)
{
	//캐릭터가 스테이지에 입장하면 대전 상태로 전환.
	SetState(EStageState::Fight);
}

void AABStageGimmick::SetReady()
{
	//가운데 트리거 활성화.
	StageTrigger -> SetCollisionProfileName(CPROFILE_ABTRIGGER);

	//플레이어가 게이트와 상호작용하지 않도록 콜리전 끄기.
	for(const auto& GateTrigger : GateTriggers)	//objetPtr 이니까.
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	// 준비 상태일 때는 문이 열려있도록 설정.
	OpenAllGates();
}

void AABStageGimmick::SetFight()	 //콜리전 반응 없어야 함.
{
	//가운데 트리거 활성화.
	StageTrigger -> SetCollisionProfileName(TEXT("NoCollision"));

	//플레이어가 게이트와 상호작용하지 않도록 콜리전 끄기.
	for(const auto& GateTrigger : GateTriggers)	//objetPtr 이니까.
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	//모든 문 닫기.
	CloseAllGates();

	//NPC 생성.
	GetWorld()->GetTimerManager().SetTimer (
		OpponentTimerHandle		//타이머 핸들
		,this					//콜백 함수 소유 객체
		,&AABStageGimmick::OpponentSpawn	//콜백함수.
		,OpponentSpawnTime		//타이머 시간 값.
		,false					//방복 여부
	);
}

void AABStageGimmick::SetChooseReward()
{
	// 가운데 트리거 활성화.
	StageTrigger->SetCollisionProfileName(TEXT("NoCollision"));

	// 플레이어가 게이트와 상호작용하지 않도록 콜리전 끄기.
	for(const auto& GateTrigger : GateTriggers)
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	// 모든 문 닫기.
	CloseAllGates();

	//보상상자 생성
	SpawnRewardBoxes();
}

void AABStageGimmick::SetChooseNext()	//문만 활성화 되어야 햐.
{
	//가운데 트리거 활성화.
	StageTrigger -> SetCollisionProfileName(TEXT("NoCollision"));

	//플레이어가 게이트와 상호작용하지 않도록 콜리전 켜기.
	for(const auto& GateTrigger : GateTriggers)	//objetPtr 이니까.
	{
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	}

	// 모든 문 열기 (다른 스테이지로 이동할 수 있도록).
	OpenAllGates();
}

void AABStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent,AActor * OtherActor,UPrimitiveComponent * OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepResult)
{
	//게이트에는 하나의태그를 설정했기 때문에 이를 확인.
	ensure(OverlappedComponent->ComponentTags.Num() == 1);

	//태그 확인 (예: +XGate)
	FName ComponentTag = OverlappedComponent->ComponentTags[0];

	//태그에서 스테이지를 배치할 소캣의 이름을 가져오기.
	FName SocketName = FName(*ComponentTag.ToString().Left(2));

	//소캣이 있는지 확인.
	check(Stage->DoesSocketExist(SocketName));	//개발단계에서 확인필요할 때 싸용하는  ensure  check - 스태틱어서트? //https://dev.epicgames.com/documentation/ko-kr/unreal-engine/asserts-in-unreal-engine

	//소캣 이름을 통해 위치 값 가져오기.
	FVector NewLocation = Stage->GetSocketLocation(SocketName);

	//가져온 위치에 이미 다른 스테이지가 없는지 확인
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(
		SCENE_QUERY_STAT(GateTrigger),
		false,
		this
	);
	// 오버랩으로 검사.
	bool Result =GetWorld()->OverlapMultiByObjectType(
		OverlapResults		//충돌 결과를 반환할 변수
		,NewLocation		//충돌 판정할 위치
		,FQuat::Identity	//회전.
		,FCollisionObjectQueryParams::InitType::AllDynamicObjects	//충돌 판정 오브젝트 채널
		,FCollisionShape::MakeSphere(775.f)							//충돌 판정할 쌔 사용할 모형,
		,CollisionQueryParams										//콜리전 옵션(자기는 제외하기 위해)
	);

	//생성하려는 위치에 다른 스테이지ㅏ가 없아면, 생성 진항.
	if(!Result)
	{
		FTransform SpawnTransform(NewLocation);

		AABStageGimmick* NewGimmick=GetWorld()->SpawnActorDeferred<AABStageGimmick>//(NewLocation,FRotator::ZeroRotator);
			(AABStageGimmick::StaticClass(),SpawnTransform);

		//새로 생성한 스테이지의 숫자를 하나 증가.
		if(NewGimmick)
		{
			NewGimmick->SetStageNum(CurrentStageNum +1);

			//생성 완료 처리.
			NewGimmick->FinishSpawning(SpawnTransform);
		}
	}
}

void AABStageGimmick::OpenAllGates()
{
	//문 액터의 배열을 순회하면서, 회전 설정.
	for(const auto& Gate:Gates)
	{
		Gate.Value->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
	}
}

void AABStageGimmick::CloseAllGates()
{
	//문 액터의 배열을 순회하면서, 회전 설정.
	for(const auto& Gate:Gates)
	{
		Gate.Value->SetRelativeRotation(FRotator::ZeroRotator/*(0.f,0.f,0.f)*/);	//요 회전 0 :
	}
}

void AABStageGimmick::OpponentDestroyed(AActor * DestroyedActor)
{
	//nPC 죽으면 보상 단계로 설정.
	SetState(EStageState::Reward);
}

void AABStageGimmick::OpponentSpawn()
{
	// NPC를 생성할 위치 설정.
	const FTransform SpawnTransform (GetActorLocation() + FVector::UpVector * 88.0f);

	// NPC 생성.
	AABCharacterNonPlayer* ABOpponentCharacter
		= GetWorld()->SpawnActorDeferred<AABCharacterNonPlayer>(OpponentClass,SpawnTransform);

	// NPC가 죽었을 때 발행되는 델리게이트에 등록.
	if(ABOpponentCharacter)
	{
		ABOpponentCharacter->OnDestroyed.AddDynamic(this,&AABStageGimmick::OpponentDestroyed);

		//현재 스테이지 레벨을 캐릭터 NPC 레벨 로 설정.
		ABOpponentCharacter->SetLevel(CurrentStageNum);

		//생성완료 처리.
		ABOpponentCharacter->FinishSpawning(SpawnTransform);
	}
}

void AABStageGimmick::OnRewardTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent,AActor * OtherActor,UPrimitiveComponent * OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepResult)
{
	//캐릭터가 보상상자를 획득하면, 상자를 배열을 순회하면서, 처리 진행.
	for(const auto& RewardBox : RewardBoxes)
	{
		//약참조여서,유효한지 꼭 확인해야 함.
		//보상상자가 유효하고, 처리 진행.
		if(RewardBox.IsValid())
		{
			//보상 상자의 포인터 가져오기.
			AABItemBox* ValidBox =  RewardBox.Get();
			AActor* OverlappedBox = OverlappedComponent->GetOwner();

			//두 박스가 서로 다른 경우 제러.
			if(OverlappedBox != ValidBox)
			{
				ValidBox->Destroy();
			}
		}
	}

	//다음 단계로 전환
	SetState(EStageState::Next);
}

void AABStageGimmick::SpawnRewardBoxes()
{
	for(const auto& RewardBoxLocation : RewardBoxLocations)
	{
		//박스 생성 위치
		FVector SpawnLocation =
			GetActorLocation() //중심위치
			+ RewardBoxLocation.Value //설정위치
			+ FVector(0.f,0.f,30.f);	//높이 보정

		FTransform SpawnTransform(SpawnLocation);

		//박스 엑터 생성
		AABItemBox* RewardBoxActor =GetWorld()->SpawnActorDeferred<AABItemBox>(
			RewardItemClass
			,SpawnTransform
		);

		//생성이 잘 됐음, 아이템 박스 타입으로 형변환.
		//AABItemBox* RewardBoxActor = Cast<AABItemBox>(ItemActor);
		if(RewardBoxActor)
		{
			//생성된 아이템 액터에 태그 추가ㅣ 나중 구분을 위해서!
			RewardBoxActor->Tags.Add(RewardBoxLocation.Key);

			// 오버랩 이벤트에 등록.
			RewardBoxActor->GetTrigger()-> OnComponentBeginOverlap.AddDynamic(this,&AABStageGimmick::OnRewardTriggerBeginOverlap);

			// 생성된 아이템 상자를 배열에 추가.
			RewardBoxes.Add(RewardBoxActor);
		}
	}

	//생성을 모두 완료한 후에 FinishSpawming() 호출.
	for(const auto& RewardBox : RewardBoxes)
	{
		if(RewardBox.IsValid())
		{
			RewardBox.Get()->FinishSpawning(RewardBox.Get()->GetActorTransform());
		}
	}
}