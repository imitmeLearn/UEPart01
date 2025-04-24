// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABCharacterStat.h"

#include "ABGameSingleton.generated.h"

//로그 카테고리 선언.
DECLARE_LOG_CATEGORY_EXTERN(LogABGameSingleton,Error,All);
/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UABGameSingleton: public UObject
{
	GENERATED_BODY()
public:
	UABGameSingleton();

	//싱글톤 접근 Get
	static UABGameSingleton& Get();
public:	//CHARACTER STAT DATA SECTION

	//레벨을 인덱스로 사용해 캐릭터 스탯을 가져올 수 있는 getter
	FORCEINLINE FABCharacterStat GetCharacterStat(int32 InLevel) const
	{
		return CharacterStatTable.IsValidIndex(InLevel -1)
			? CharacterStatTable[InLevel -1]
			: FABCharacterStat();
	}

	UPROPERTY()
		int32 CharacterMaxLevel;	//최대레벨

private:
	//스텟을 배열로 관리
	TArray<FABCharacterStat> CharacterStatTable;
};
