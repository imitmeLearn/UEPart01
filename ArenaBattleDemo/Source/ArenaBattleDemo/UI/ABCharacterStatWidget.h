// Fill out your copyright notice in the Description page of Project Settings.//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ABCharacterStat.h"
#include "ABCharacterStatWidget.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UABCharacterStatWidget: public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStat(
	const FABCharacterStat& BaseStat
		,const FABCharacterStat& ModifierStat
	);

private:
	//스퉷 위젯이 가진 텍스트 블록 저장하는 맵
	UPROPERTY()
		TMap<FName,class UTextBlock*> BaseLookup;
	//스퉷 위젯이 가진 텍스트 블록 저장하는 맵
	UPROPERTY()
		TMap<FName,class UTextBlock*> ModifierLookup;
};
