// Fill out your copyright notice in the Description page of Project Settings.//

#include "AI/MyBTService_Detect.h"
#include "AIController.h"
#include "Physics/ABCollision.h"
#include "Interface/ABCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ABAI.h"

UMyBTService_Detect::UMyBTService_Detect()
{
	//에디터에서 보이는 이름 설정.
	NodeName = TEXT("Detect");

	//Tick 이 실행되는 주기 설정.
	Interval = 1.f;
}

void UMyBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory,float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

	//aI Controller 가 제어하는폰.
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(!ControllingPawn)
	{
		return;
	}

	//인터페이스 형변환
	IABCharacterAIInterface* AIPawn = Cast<IABCharacterAIInterface>(ControllingPawn);
	if(!AIPawn)
	{
		return;
	}

	//월드정보.
	UWorld* World = ControllingPawn->GetWorld();

	//충돌감지
	TArray <FOverlapResult> OverlapResults;

	//감지 시작위치.
	FVector Center = ControllingPawn->GetActorLocation();

	//감지 범위 설정
	float DetectRadius = AIPawn->GetAIDetectRange();	/*#include "Interface/ABCharacterAIInterface.h"*/

	//충돌 제외 목록 설정.
	FCollisionQueryParams CollisionQueryParams(
		SCENE_QUERY_STAT(Detect)
		,false
		,ControllingPawn
	);

	//감지처리.
	bool bResult =	World->OverlapMultiByChannel(
			OverlapResults
			,Center
			,FQuat::Identity
			,CCHANNEL_ABACTION	/* #include "Physics/ABCollision.h" */
			,FCollisionShape::MakeSphere(DetectRadius)
			,CollisionQueryParams
	);

	//충돌 감지되면,
	if(bResult)
	{
		//감지된 플레이어에 대해 처리 진행.
		for(auto const& OverlapResult : OverlapResults)
		{
			//감지된 엑터를 폰으로 형변환.
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());

			//플레이어 인지 확인.
			if(Pawn && Pawn->GetController()->IsPlayerController())
			{
				//감지한 플레이어를 블랙보드에 저장
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(
					BBKEY_TARGET,Pawn
				);

				//디버그 드로우 를 활용해 감지 영역을 녹색으로 표시.
				DrawDebugSphere(
					World
					,Center
					,DetectRadius
					,16
					,FColor::Green
					,false
					,0.2f
				);

				//감지지점 을 포인트, 녹색으로 표시.
				DrawDebugPoint(
					World
					,Pawn->GetActorLocation()
					,10.f
					,FColor::Green
					,false
					,.2f
				);

				//감지 된 방향을, 녹색으로 표시.
				DrawDebugLine(
					World
					,ControllingPawn->GetActorLocation()
					,Pawn->GetActorLocation()
					,FColor::Green
					,false
					,.2f
				);

				return;
			}
		}
	}

	// 플레이어 감지 실패.
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET,nullptr);

	//디버그 드로우 를 활용해 감지 영역을 빨강색으로 표시.
	DrawDebugSphere(
		World
		,Center
		,DetectRadius
		,16
		,FColor::Red		/*빨강색*/
		,false
		,0.2f
	);
}