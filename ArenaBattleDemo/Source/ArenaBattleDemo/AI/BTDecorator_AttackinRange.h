// Fill out your copyright notice in the Description page of Project Settings.//

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AttackinRange.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UBTDecorator_AttackinRange: public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_AttackinRange();
protected:

	//데코레이터실행에 필요한 함수.
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) const;
};
