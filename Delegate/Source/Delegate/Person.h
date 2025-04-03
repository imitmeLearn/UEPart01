// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 *
 */
UCLASS()
class UNREALDELEGATE_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	const FString& GetName() const;
	void SetName(const FString& InName);

	class UCard* GetCard() const;
	void SetCard(class UCard* InCard);

protected:
	//언리얼의 관리를 받도록!
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;
	UPROPERTY()
	//class UCard* Card;
	TObjectPtr<class UCard> Card;
};
