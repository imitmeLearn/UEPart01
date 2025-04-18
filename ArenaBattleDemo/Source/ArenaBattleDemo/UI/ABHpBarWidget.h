// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABHpBarWidget.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API UABHpBarWidget: public UUserWidget
{
	GENERATED_BODY()

public:
	UABHpBarWidget(const FObjectInitializer& ObjectInitializer);

	// 최대 체력 설정 함수.
	FORCEINLINE void SetMaxHp(float NewMaxHp)
	{
		MaxHp = NewMaxHp;
	}

	// HpBar에 퍼센트를 조정할 때 호출할 함수.
	void UpdateHpBar(float NewCurrentHp);

protected:
	virtual void NativeConstruct() override;	//UMG 가 초기화 될때 호출되는 함수.
protected:
	//HP 게이지를 보여주기 위해 사용할 프로그레스바 참조 변수
	UPROPERTY()
		TObjectPtr<class UProgressBar> HpProgressBar;

	//최대 체력 값.
	UPROPERTY()
		float MaxHp;
};
