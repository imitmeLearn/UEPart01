// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("ȫ�浿");
	Year = 1;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT(" %s ���� ������ �����մϴ�. "), *Name);
}

const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& InName)
{
	Name = InName;
}