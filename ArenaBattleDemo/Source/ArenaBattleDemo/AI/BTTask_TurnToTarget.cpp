// Fill out your copyright notice in the Description page of Project Settings.//

#include "AI/BTTask_TurnToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/ABCharacterAIInterface.h"
#include "ABAI.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp,NodeMemory);	//AB내적 == cs

	//컨트롤러가 제어하는 폰.
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	//플레이어.
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if(!TargetPawn)
	{
		return EBTNodeResult::Failed;
	}

	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if(!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	//회전할 속도
	float TurnSpeed = AIPawn->GetAITurnSpeed();

	//바라볼 방향
	FVector LookVector = TargetPawn->GetActorLocation()-ControllingPawn->GetActorLocation();

	//높이성분은 제거
	LookVector.Z =0.f;

	//바라볼 방향을 이용해 FRotator 구하기
	FRotator TargetRot =	FRotationMatrix::MakeFromX(LookVector).Rotator();

	// 부드럽게 회전 설정.

	//현재 프레임에 설정할 회전 값.
	FRotator CurrentRot = FMath::RInterpTo(
		ControllingPawn->GetActorRotation()
		,TargetRot
		,GetWorld()->DeltaTimeSeconds
		,TurnSpeed
	);

	return EBTNodeResult::Type();
}