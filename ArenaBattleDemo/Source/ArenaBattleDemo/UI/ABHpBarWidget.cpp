// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ABHpBarWidget.h"
#include "Components/ProgressBar.h"

UABHpBarWidget::UABHpBarWidget(const FObjectInitializer & ObjectInitializer)
	:Super (ObjectInitializer)
{
	//일부로  유효하지 않은 음수값를 넣어서, 구분하기 위해서, 값 설정.
	MaxHp = -1.f;
}

void UABHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.f);	//MAX 값이 제대로 설정됐는지 확인.
	//프로그래스 바  위젯 업데이트.
	if(HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp/MaxHp);
	}
}

void UABHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//이 함수가 호출되면,UI 에 대한 대부분의 값이 되기화 되었다고 생각할 수 있음.

	HpProgressBar=	Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));		//위젯 참조 설정을 위해 이름으로 검색.
	ensure(HpProgressBar);
}