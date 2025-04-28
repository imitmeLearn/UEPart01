// Fill out your copyright notice in the Description page of Project Settings.//

#include "AI/BTDecorator_AttackinRange.h"
#include "AIController.h"
#include "Interface/ABCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ABAI.h"

UBTDecorator_AttackinRange::UBTDecorator_AttackinRange()
{
	//에디터에서 보일 노드 이름 설정.
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp,NodeMemory);

	//AI Controllder 제어하는 폰.
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return false;
	}

	IABCharacterAIInterface* AIPawn
		= Cast<IABCharacterAIInterface>(ControllingPawn);
	if(!AIPawn)
	{
		return false;
	}

	//판단하는데 사용될, 블랙보드 에 저장된 캐릭터 값.
	APawn* Target = Cast<APawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET)
	);
	if(!Target)
	{
		return false;
	}

	//캐릭터와의 거리 계산
	float DistanceToTarget = ControllingPawn -> GetDistanceTo(Target);

	//공격범위 값.
	float AttackRangeWithRadius = AIPawn->GetAIAttactRange();

	////캐럭터와 거리가 공격 가능거리보다 가까운지 확인 후 결과 변환.
	bResult = (DistanceToTarget <= AttackRangeWithRadius);

	return bResult;
}