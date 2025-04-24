// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

// 상태에 따른 처리를 위한 델리게이트 선언.
DECLARE_DELEGATE(FOnStageChangedDelegate);

// 래퍼 구조체.
USTRUCT(BlueprintType)
struct FOnStageChangedDelegateWrapper
{
	GENERATED_BODY()

		FOnStageChangedDelegateWrapper() {}
	FOnStageChangedDelegateWrapper(FOnStageChangedDelegate InDelegate)
		: StageChangedDelegate(InDelegate) {}

	FOnStageChangedDelegate StageChangedDelegate;
};

//상태를 나타내는 열거형
UENUM(BlueprintType)
enum class EStageState: uint8
{
	Ready =0
	,Fight
	,Reward
	,Next
};

UCLASS()
class ARENABATTLEDEMO_API AABStageGimmick: public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABStageGimmick();

	//트랜스폼 뿐만 아니라, 다른 속성이 변경되는 경우에 호출됟로고 해주는 함수!
	virtual void OnConstruction(const FTransform& Transform) override;
public:	//STAT SECTION

	//CurrentStageNum 에 대한 GETTER/SETTER
	FORCEINLINE int32 GetStageNum() const
	{
		return CurrentStageNum;
	}
	FORCEINLINE void SetStageNum(int32 InNewStageNum)
	{
		CurrentStageNum = InNewStageNum;
	}

protected:	//STAGE SECTION

	// 스테이지를 보여줄 때 사용할 메시 컴포넌트.
	UPROPERTY(VisibleAnywhere,Category = Stage,meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> Stage;
	UPROPERTY(VisibleAnywhere,Category = Stage,meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UBoxComponent> StageTrigger;

	//현재 상태를 나타내는 열거형 변수.
	UPROPERTY(EditAnywhere,Category = Stage,meta = (AllowPrivateAccess = "true"))
		EStageState CurrentState;

	//상태를 설정할 때 사용할 함수.
	void SetState(EStageState InNewState);

	//스테이지 트리거의 오버랩 이벤트 확인을 위한 함수
		/*DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams(FComponentBeginOverlapSignature,UPrimitiveComponent,OnComponentBeginOverlap,UPrimitiveComponent*,OverlappedComponent,AActor*,OtherActor,UPrimitiveComponent*,OtherComp,int32,OtherBodyIndex,bool,bFromSweep,const FHitResult &,SweepResult);*/

	UFUNCTION()
		void OnStageTriggerBeginOverlap(
			UPrimitiveComponent* OverlappedComponent
			,AActor* OtherActor
			,UPrimitiveComponent* OtherComp
			,int32 OtherBodyIndex
			,bool bFromSweep
			,const FHitResult& SweepResult
		);

	//상태에 따른 처리를 위해 열거형과 델리게이트를 맵으로 관리
	UPROPERTY()
		TMap<EStageState,FOnStageChangedDelegateWrapper> StageChangedActions;

	//상태 값에 따라 실행할 함수.
	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();

protected:	//GATE SECTION (4개 문의 대한 섹션)
	// 4개의 게이트(문)가 필요하기 때문에 Map으로 관리.
	UPROPERTY(VisibleAnywhere,Category = Gate,meta = (AllowPrivateAccess = "true"))
		TMap<FName,TObjectPtr<class UStaticMeshComponent>> Gates;

	//각 문의 트리거를 배열로 관리
	UPROPERTY(VisibleAnywhere,Category = Gate,meta = (AllowPrivateAccess = "true"))
		TArray<TObjectPtr<class UBoxComponent>> GateTriggers;

	//게이트 트리거의 오버랩 이벤트 확인을 위한 함수
	UFUNCTION()
		void OnGateTriggerBeginOverlap(
			UPrimitiveComponent* OverlappedComponent
			,AActor* OtherActor
			,UPrimitiveComponent* OtherComp
			,int32 OtherBodyIndex
			,bool bFromSweep
			,const FHitResult& SweepResult
		);

	void OpenAllGates();
	void CloseAllGates();

protected:	//FIGHT SECTION
	//대전할NPC 지정을 위한 클래스 변수 선언
	//TSubclassOf 는 지정한 클래스를 제한적으로 보여주는 필터링을 제공함.
	UPROPERTY(EditAnywhere,Category = Fight,meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AABCharacterNonPlayer> OpponentClass;

	//NPC 생성하기 까지 대기할 시간
	UPROPERTY(EditAnywhere,Category = Fight,meta = (AllowPrivateAccess = "true"))
		float OpponentSpawnTime;

	//NPC 무찔렀을 때, 실행할 함수.
	UFUNCTION()
		void OpponentDestroyed(AActor* DestroyedActor);

	// NPC 생성 시간을 계산할 타이머 핸들.
	FTimerHandle OpponentTimerHandle;

	// 타이머가 종료되어 NPC가 생성될 때 호출할 함수.
	void OpponentSpawn();

protected:	////REWARD SECTION
	//보상상자 -
	//없으면, 클래스 모드 필요
	//보상상자 생성을 위한 클래스,
	UPROPERTY(VisibleAnywhere,Category = Reward,meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AABItemBox> RewardItemClass;

	//박스 런타임 생성 시, 오버랩 판정하고, 자체는 생성로직에 등록가능하나, 여러개 생성 시, 하나랑 충돌하면, 충돌안한 나머지 지워야 하니, 생성한것들을 배열로 관리해야 한다.
	//강참조는 objectPtr 약참조는 TWeakObjectPtr
	TArray<TWeakObjectPtr<class AABItemBox>> RewardBoxes;

	//보상 상자 생성 위치 맵으로 관리.
	TMap<FName,FVector> RewardBoxLocations;

	//생성된 상자와의 오버랩 이벤트를 처리할 때 사용할 함수.
	//딜리게이트 연결을 위한, 인자-파라미터!
	UFUNCTION()
		void OnRewardTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent
		,AActor* OtherActor
		,UPrimitiveComponent* OtherComp
		,int32 OtherBodyIndex
		,bool bFromSweep
		,const FHitResult& SweepResult
		);

	//보상상자 생성은, 함수에서
	//보상상제 생성 함수.
	void SpawnRewardBoxes();

protected:	////STAGE STAT SECTION
	UPROPERTY(VisibleInstanceOnly,Category = Stat,meta = (AllowPrivateAccess = "true"))
		int32 CurrentStageNum;
};
