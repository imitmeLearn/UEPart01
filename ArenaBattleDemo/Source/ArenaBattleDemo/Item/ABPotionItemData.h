﻿// Fill out your copyright notice in the Description page of Project Settings.//

#pragma once

#include "CoreMinimal.h"
#include "Item/ABItemData.h"
#include "GameData/ABCharacterStat.h"

#include "ABPotionItemData.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UABPotionItemData: public UABItemData
{
	GENERATED_BODY()

public:
	UABPotionItemData();
public:
	//캐릭터 기본 스탯 데이터

	UPROPERTY(EditAnywhere,Category = Hp)
		float HealAmount;
	//FABCharacterStat BaseStat;
};
