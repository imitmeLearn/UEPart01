﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Staff.h"
#include "Card.h"

UStaff::UStaff()
{
	Name = TEXT("장직원");
	Card->SetCardType(ECardType::Staff);
}