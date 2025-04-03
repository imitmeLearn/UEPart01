// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LessonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULessonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class DELEGATE_API ILessonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void DoLesson() = 0; //순수 추상함수.
	virtual void DoLesson()
	{
		UE_LOG(LogTemp, Log, TEXT("수업 입장"));
	}
};
