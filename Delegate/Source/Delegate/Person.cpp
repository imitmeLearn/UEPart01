// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("홍길동");
	Year = 1;
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}

const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& InName)
{
	Name = InName;
}

UCard* UPerson::GetCard() const
{
	return Card;
}

void UPerson::SetCard(UCard* InCard)
{
	Card = InCard;
}