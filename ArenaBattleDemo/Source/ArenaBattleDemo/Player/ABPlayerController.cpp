// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ABPlayerController.h"
#include "UI/ABHUDWidget.h"
#include "ABSaveGame.h"
#include <Kismet\GameplayStatics.h>

DEFINE_LOG_CATEGORY(LogABPlayerController);

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

	//게임이 끝나면, 세이브 게임을 활용해 데이터 저장.
	if(!UGameplayStatics::SaveGameToSlot(SaveGameInstance,TEXT("Player0"),0))
	{
		UE_LOG(LogABPlayerController,Error,TEXT("SaveGameError!"));
	}

	//게임 시작할 떄도, 재시도 횟수 정보를 알 수 있도록 이벤트 발생.
	K2_OnGameRetryCount(SaveGameInstance->RetryCount);
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 시작할 때 마우스가 뷰포트로 입력되어 바로 실행하도록 설정
	FInputModeGameOnly GameInput;
	SetInputMode(GameInput);

	//게임이 시작되면, 저장된 게임이 있는지 먼저 확인하고, 이를 로드
	//LoadGameFromSlot> 저장된 게임을 로드할 때 ㅅ용.
	//1. 저장할 파일이름.
	//2. 플레이어 아이디>실글 플레이어 게임의 경우 항상 0
	SaveGameInstance = Cast<UABSaveGame>
		(UGameplayStatics::LoadGameFromSlot(TEXT("Player0"),0));
	if(SaveGameInstance)
	{
		SaveGameInstance->RetryCount++;
	} else
	{
		SaveGameInstance = NewObject<UABSaveGame>();
	}

	//게임 시작할 떄도, 재시도 횟수 정보를 알 수 있도록 이벤트 발생.
	K2_OnGameRetryCount(SaveGameInstance->RetryCount);

	////위젯 생성 -> 블루프린트에 작성
	//ABHUDWidget = CreateWidget<UABHUDWidget>(this,ABHUDWidgetClass);
	//if(ABHUDWidget)
	//{
	//	//위젯 화면에 추가해, UI 가 보일 수 있도록 설정.
	//	ABHUDWidget->AddToViewport();
	//}
}