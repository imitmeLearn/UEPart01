// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

struct FStudentData
{
	FStudentData()
	{
	}
	FStudentData(int32 InOrder, const FString& InName)
		:Order(InOrder), Name(InName)
	{
	}
	int32 Order = -1;
	FString Name = TEXT("ȫ�浿");
};
/**
 *
 */
UCLASS()
class UNREALSERIALIZATION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();
	virtual void Init() override;
};
