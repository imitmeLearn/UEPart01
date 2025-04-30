// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ABHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"	//UTextBlock
#include "Interface/ABCharacterWidgetInterface.h"
#include "Character/ABCharacterBase.h"

UABHpBarWidget::UABHpBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//일부로  유효하지 않은 음수값를 넣어서, 구분하기 위해서, 값 설정.
	MaxHp = -1.f;
}

void UABHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	//현재 hp 값 업데이트.
	CurrentHp = NewCurrentHp;

	ensure(MaxHp > 0.f);	//MAX 값이 제대로 설정됐는지 확인.
	//프로그래스 바  위젯 업데이트.
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(CurrentHp / MaxHp);
	}

	//HP 스텟 텍스트 업데이트.
		// 텍스트 블록이 유효하면,
	if (HpStat)
	{
		HpStat->SetText(FText::FromString(GetHpStatText()));
	}
}

void UABHpBarWidget::UpdateStat(const FABCharacterStat& BaseStat, const FABCharacterStat& ModifierStat)
{
	//최고
	MaxHp = (BaseStat + ModifierStat).MaxHp;

	// 프로그레스바가 유효하면,
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(CurrentHp / MaxHp);
	}

	// 텍스트 블록이 유효하면,
	if (HpStat)
	{
		HpStat->SetText(FText::FromString(GetHpStatText()));
	}
}

FString UABHpBarWidget::GetHpStatText()
{
	return FString::Printf(TEXT("%.0f / %.0f"), CurrentHp, MaxHp);
}

void UABHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//이 함수가 호출되면,UI 에 대한 대부분의 값이 되기화 되었다고 생각할 수 있음.

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));		//위젯 참조 설정을 위해 이름으로 검색.
	ensure(HpProgressBar);

	HpStat = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtHpStat")));
	ensure(HpStat);

	//..내정보 전달이 하고싶어. : 캐릭터에 내 정보(위젯)을 전달. 강참조 발생하니. 인터페이스를 통해 우회해 전달 (느슨한 결합)
	IABCharacterWidgetInterface* CharacterWidget = Cast<IABCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);		//인터페이스를 통해서 캐릭터에 내 정보(위젯)전달.
	}
}