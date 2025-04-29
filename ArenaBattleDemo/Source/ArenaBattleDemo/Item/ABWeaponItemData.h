// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ABItemData.h"
#include "GameData/ABCharacterStat.h"

#include "ABWeaponItemData.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UABWeaponItemData: public UABItemData
{
	GENERATED_BODY()
public:
	UABWeaponItemData();
public:
	/*
	//오버라이드 FPrimaryAssetId 값 반환하는
	 첫번째 인자 : 태그값: 프로젝트 세팅에서 넣은 이름이랑 같은거 적기*/
	 /*두번째 인자 : 이름값: 일반적으로GetFName() 많이 활용함, 오브젝트 마다 고유이름을 갖기 때문에. 직접지정도 가능함.*/
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(
			"ABItemData"
			,GetFName()
		);
	}
public:
	// 제공할 무기에 대한 스켈레탈 메시.
	UPROPERTY(EditAnywhere,Category = Weapon)
		TSoftObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere,Category = Stat)
		FABCharacterStat ModifierStat;
};
