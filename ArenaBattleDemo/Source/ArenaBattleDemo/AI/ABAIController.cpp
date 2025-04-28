// Fill out your copyright notice in the Description page of Project Settings.//

#include "AI/ABAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ABAI.h"

AABAIController::AABAIController()
{
	////에셋로드
	//블랙 보드 에셋
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/ArenaBattle/AI/BB_ABCharacter.BB_ABCharacter"));
	if(BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	//행동 트리 에셋
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/ArenaBattle/AI/BT_ABCharacter.BT_ABCharacter"));
	if(BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AABAIController::RunAI()
{
	//블랙보드 컴포넌트 포인터 가져오기.
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();

	//사용할 블랙보드 지정.
	if(UseBlackboard(BBAsset,BlackboardPtr))
	{
		//시작할 때 npc 위치를 블랙보드에 BBKEY_HOMEPOS에 저장.
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS,GetPawn()->GetActorLocation());	//폰 위치 저장.

		//행동트리 실행.
		bool RunResult = RunBehaviorTree(BTAsset);
		//실행에 실패하면 확인.
		ensure(RunResult);
	}
}

void AABAIController::StopAI()
{
	// 중지를 위해 실행 중인 BehaviorTreeComponent 가져오기.
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent> (BrainComponent); //다운케스팅!

	// BT 중지.
	if(BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AABAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	//컨트롤라가 폰에 빙의하면, AI 를 실행.
	RunAI();
}