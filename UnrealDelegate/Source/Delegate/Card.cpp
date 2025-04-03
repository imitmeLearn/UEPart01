// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"

UCard::UCard()
{
	CardType = ECardType::InValid;
	Id = 0;
}

ECardType UCard::GetCardType() const
{
	return CardType;
}
void UCard::SetCardType(ECardType InCardType)
{
	CardType = InCardType;
}