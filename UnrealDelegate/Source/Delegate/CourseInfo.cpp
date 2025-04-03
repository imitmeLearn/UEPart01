// Fill out your copyright notice in the Description page of Project Settings.

#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
	Contents = TEXT("기본학사정보");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
	//콘텐츠 업데이트
	Contents = InNewContents;
	//발행
	OnChanged.Broadcast(InSchoolName, InNewContents);
}