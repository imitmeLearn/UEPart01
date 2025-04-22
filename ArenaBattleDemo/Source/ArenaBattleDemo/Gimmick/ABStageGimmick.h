﻿// Fill out your copyright notice in the Description page of Project Settings.

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
public:
};
