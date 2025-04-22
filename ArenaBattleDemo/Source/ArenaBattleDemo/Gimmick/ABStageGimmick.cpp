// Fill out your copyright notice in the Description page of Project Settings.

#include "Gimmick/ABStageGimmick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Physics/ABCollision.h"

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
{}

void AABStageGimmick::SetReady()
{
	//가운데 트리거 활성화.
	StageTrigger -> SetCollisionProfileName(CPROFILE_ABTRIGGER);

	//플레이어가 게이트와 상호작용하지 않도록 콜리전 끄기.
	for(const auto& GateTrigger : GateTriggers)	//objetPtr 이니까.
	{
		GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	}

	//모든 문 닫기.
	CloseAllGates();
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
}

void AABStageGimmick::SetChooseReward()
{}

void AABStageGimmick::SetChooseNext()	//문만 활성화 되어야 햐.
{
	//가운데 트리거 활성화.
	StageTrigger -> SetCollisionProfileName(TEXT("NoCollision"));

	//플레이어가 게이트와 상호작용하지 않도록 콜리전 끄기.
	for(const auto& GateTrigger : GateTriggers)	//objetPtr 이니까.
	{
		GateTrigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	}

	//모든 문 닫기.
	OpenAllGates();
}

void AABStageGimmick::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent,AActor * OtherActor,UPrimitiveComponent * OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepResult)
{}

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