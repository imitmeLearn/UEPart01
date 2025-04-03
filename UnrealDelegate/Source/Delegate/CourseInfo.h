// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "functional"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInforOnChanged, const FString&, const FString&);

//std::function<void(const FString&, const FString&)> CourseInfo;

/**
 *
 */
UCLASS()
class DELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
public:
	UCourseInfo();

	FCourseInforOnChanged OnChanged;

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	UPROPERTY()
	FString Contents;
};
