// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABItemData.generated.h"
// 아이템 종류 열거형.
// 블루프린트와 호환되도록 BlueprintType 지정.
UENUM(BlueprintType)
enum class EItemType:uint8
{
	Weapon=0
	,Position
	,Scroll
};
/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UABItemData: public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//오버라이드 FPrimaryAssetId 값 반환하는
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(
			"ABItemData"	/*태그값: 프로젝트 세팅에서 넣은 이름이랑 같은거 적기*/
			,GetFName()		/*이름값: 일반적으로GetFName() 많이 활용함, 오브젝트 마다 고유이름을 갖기 때문에. 직접지정도 가능함.*/
		);
	}

public:
	//아이템 타입을 지정하는 열거형 변수.
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Type)
		EItemType Type;
};
