﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"

AABPlayerController::AABPlayerController()
{
	// 위젯 블루프린트 애셋에서 클래스 정보 로드.
	///Script/UMGEditor.WidgetBlueprint''
	static ConstructorHelpers::FClassFinder<UABHUDWidget> ABHUDWidgetRef(TEXT("/Game/ArenaBattle/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if(ABHUDWidgetRef.Class)
	{
		ABHUDWidgetClass = ABHUDWidgetRef.Class;
	}
}

void AABPlayerController::GameScoreChanged(int32 NewScore)
{
	K2_OnScoreChanged(NewScore);
}

void AABPlayerController::GameClear()
{
	K2_OnGameClear();
}

void AABPlayerController::GameOver()
{
	K2_OnGameOver();
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 시작할 때 마우스가 뷰포트로 입력되어 바로 실행하도록 설정
	FInputModeGameOnly GameInput;
	SetInputMode(GameInput);

	////위젯 생성 -> 블루프린트에 작성
	//ABHUDWidget = CreateWidget<UABHUDWidget>(this,ABHUDWidgetClass);
	//if(ABHUDWidget)
	//{
	//	//위젯 화면에 추가해, UI 가 보일 수 있도록 설정.
	//	ABHUDWidget->AddToViewport();
	//}
}