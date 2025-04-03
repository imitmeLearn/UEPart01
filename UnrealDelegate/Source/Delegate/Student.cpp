﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("장학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("수업 듣기 : %s "), *Name);
}

void UStudent::GetNotification(const FString& InSchool, const FString& InNewCourseInfo)
{
	UE_LOG(LogTemp, Log, TEXT("[Student] %s 님이, %s 로부터 받은 메시지 : %s ")
		, *Name, *InSchool, *InNewCourseInfo);
}