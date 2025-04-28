// Fill out your copyright notice in the Description page of Project Settings.//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_Detect.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UMyBTService_Detect: public UBTService
{
	GENERATED_BODY()

public:
	UMyBTService_Detect();
	virtual	void TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory,float DeltaSeconds) override;
};
