// Fill out your copyright notice in the Description page of Project Settings.//

#include "AI/BTTask_FindPatrolPos.h"
#include "ABAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp,NodeMemory);

	//네비게이션 시스템을 사용해 랜덤으로 이동 가능한 위치를 구한 뒤에, 블랙보드 정찰 위치로 저장.

	//비헤이비어트리를 소유하는 컨트롤러가 제어하는 폰 정보 가져오기.
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem =  UNavigationSystemV1::GetNavigationSystem(

		ControllingPawn->GetWorld()
	);

	//유효한지 검사
	if(!NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	//폰이 생성된 초기 위치 가져오기.
	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);

	//결과 저장을 위한 변수
	FNavLocation NextPatrolPos;
	if(NavSystem->GetRandomPointInNavigableRadius(Origin,800.f,NextPatrolPos))
	{
		//OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS,NextPatrolPos);	//가능 :내부적으로 형변환 연산자 있음 + cpp 에서 암시적으로 형변환 진행하는데, 그 둘이 맞아서 가능!
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS,NextPatrolPos.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}