﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Student.h"

UStudent::UStudent()
{
	Name = TEXT("장학생");
	Year = 1;
	Id = 1;
}

void UStudent::DoLesson()
{
	Super::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d 학년 %d 학생 %s 님이 수업을 듣습니다. "), Year, Id, *Name);
}