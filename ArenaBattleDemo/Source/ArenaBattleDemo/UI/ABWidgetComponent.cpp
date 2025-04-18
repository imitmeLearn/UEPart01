// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ABWidgetComponent.h"
#include "ABUserWidget.h"

void UABWidgetComponent::InitWidget()
{
	//InitWidget 함수가 호출되면,  widgetClass 정보를 바탕으로 위젯 인스턴스를 생성함.
	//내부에서 CreateWidget 함수를 실행.
	Super::InitWidget();

	UABUserWidget* ABUserWidget = Cast<UABUserWidget>(GetWidget());		//Super::InitWidget() 함수 호출 이후에는 위젯 인스턴스가 있다(GetWidget())고 확인할 수 있음.
	if(ABUserWidget)
	{
		ABUserWidget->SetOwningActor(GetOwner());
	}
}