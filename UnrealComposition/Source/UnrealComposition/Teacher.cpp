// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("장선생");
	Year = 5;
	Id = 1;
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("수업 진행 : %s "), *Name);
}