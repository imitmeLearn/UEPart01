// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"
#include "Card.h"

UTeacher::UTeacher()
{
	Name = TEXT("장선생");
	Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("수업 진행 : %s "), *Name);
}