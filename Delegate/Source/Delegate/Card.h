// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

//열거형 선언
UENUM()
enum class ECardType : uint8
{
	Student = 1 UMETA(DisplayName = "For Student")
	, Teacher UMETA(DisplayName = "For Teacher")
	, Staff UMETA(DisplayName = "For Staff")
	, InValid
};

/**
 *
 */
UCLASS()
class UNREALDELEGATE_API UCard : public UObject
{
	GENERATED_BODY()

public:
	UCard();
	ECardType GetCardType() const;
	void SetCardType(ECardType InCardType);

private:
	UPROPERTY()
	ECardType CardType;
	UPROPERTY()
	int32 Id;
};
