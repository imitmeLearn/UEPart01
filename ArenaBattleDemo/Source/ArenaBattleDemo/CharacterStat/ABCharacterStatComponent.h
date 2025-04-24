// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ABCharacterStat.h"

#include "ABCharacterStatComponent.generated.h"

// 델리게이트 선언.

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);				// 체력 값이 0이 되었을 때 발행할 델리게이트.
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate,float /*CurrentHp*/);			// 체력 변경이 발생할 때 발행할 델리게이트.

UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent))
class ARENABATTLEDEMO_API UABCharacterStatComponent: public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	//Getter. __ 안붙이려고, 타입 재정의?
	/*FORCEINLINE float GetMaxHP()
	{
		return MaxHp;
	}*/
	FORCEINLINE float GetCurrnetHP()
	{
		return CurrentHp;
	}

	//캐릭터 레벨 설정 함수
	void SetLevelStat(int32 InNewLevel);
	FORCEINLINE float GetCurrnetLevel() const
	{
		return CurrentLevel;
	}

	//부가 스텟 데이터 설정 함수
	FORCEINLINE void SetModifierStat(const FABCharacterStat& InModifierStat)
	{
		ModifierStat = InModifierStat;
	}

	// 전체 스탯 데이터 반환 함수.
	FORCEINLINE FABCharacterStat GetTotalStat() const
	{
		return BaseStat + ModifierStat;
	}

	//데미지 전달 함수.
	float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);	//HP 변경됐을 때 실행할 함수
public:
	FOnHpZeroDelegate OnHpZero;			//체력을 모두 소진했을 때
	FOnHpChangedDelegate OnHpChanged;	//체력 변경 델리게이트

protected:	//스탯
	// 최대 체력 값.

	// 최대 체력 값.-임시로 사용하던 데이터 제거 (비활성화).
	/*UPROPERTY(VisibleInstanceOnly,Category = Stat)
		float MaxHp;*/ //-> BaseStat.Maxhp 로 변경

		// 현재 체력 값.
		// Transient: 현재 체력 값은 게임을 진행할 때마다 바뀌는 값.
		// 따라서 디스크에 명시적으로 저장할 필요하지 않을 수 있음.
		// 이럴 때는 Transient로 지정 가능.
	UPROPERTY(Transient,VisibleInstanceOnly,Category = Stat)
		float CurrentHp;

	//현재레벨.
	UPROPERTY(Transient,VisibleInstanceOnly,Category = Stat)
		float CurrentLevel;

	//캐릭터 기본 스텟 데이터
	UPROPERTY(Transient,VisibleInstanceOnly,Category = Stat,meta =(AllowPrivateAcess = "true"))
		FABCharacterStat BaseStat;

	//부가 스텟 데이터
	UPROPERTY(Transient,VisibleInstanceOnly,Category = Stat,meta =(AllowPrivateAcess = "true"))
		FABCharacterStat ModifierStat;
};
