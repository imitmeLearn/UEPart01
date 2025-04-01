// Fill out your copyright notice in the Description page of Project Settings.

#include "Student.h"

UStudent::UStudent()
{
	Name = TEXT("장학생");
	Year = 1;
	Id = 1;
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("수업 듣기 : %s "), *Name);
}