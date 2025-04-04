// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

//Declare Structure
USTRUCT()
struct FStudentData
{
	GENERATED_BODY()
	FStudentData()
		:Order(-1), Name(TEXT("ȫ�浿"))
	{
	}

	FStudentData(int32 InOrder, const FString& InName)
		:Order(InOrder), Name(InName)
	{
	}
	UPROPERTY()
	int32 Order = -1;
	UPROPERTY()
	FString Name;
};
/**
 *
 */
UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
private:
	TArray<FStudentData> StudentData;
};
