﻿// Fill out your copyright notice in the Description page of Project Settings.//

#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "Interface/ABCharacterAIInterface.h"

UBTTask_Attack::UBTTask_Attack()
{}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp,uint8 * NodeMemory)
{
	EBTNodeResult::Type Result =  Super::ExecuteTask(OwnerComp,NodeMemory);

	//AIController 가 제어하는 폰.
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	//인터페이스 형변화
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if(!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	//공경 전에 델리게이트 바인드를 해야 함.
	FAICharacterAttackFinished	 onAttackfinished;

	//람다 사용해, 델리게이트 바인딩.
	onAttackfinished.BindLambda(
	[&]()
	{
		//캐릭터의 공격이 끝날 때, 테스트를 끝나는 값 전달.
		//변환 후 테스크를 최종 마무리할 때는, FinishlatenTask 함수를 사용
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);;
	}
	);

	//z캐릭터가 공격을 종료할 때, 실행할 델리게이트 전달. 설정
	AIPawn->SetAIAttackDelegate(onAttackfinished);

	// 공격 명령 실행.
	AIPawn->AttackByAI();

	// 공격 명령 실행 후 곧바로 결과를 알 수 없기 때문에
	// 진행중(InProgress) 값을 반환.
	return EBTNodeResult::InProgress;
}