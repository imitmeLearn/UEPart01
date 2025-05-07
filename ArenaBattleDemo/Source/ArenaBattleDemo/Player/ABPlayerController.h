// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API AABPlayerController: public APlayerController
{
	GENERATED_BODY()

public:
	AABPlayerController();

	//블루프린트에 이벤트 발생기켜주는 함수.
	//K2 접두어 : Kismet 접두어를 의미 : Kismet 은 블루프린트의 전신.
	UFUNCTION(BlueprintImplementableEvent,Category=Game,meta =(DisplayName="OnScoreChangedCpp"))
		void K2_OnScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent,Category = Game,meta = (DisplayName = "OnGameClearCpp"))
		void K2_OnGameClear();

	UFUNCTION(BlueprintImplementableEvent,Category = Game,meta = (DisplayName = "OnGameOverCpp"))
		void K2_OnGameOver();

	//게임 처리와 관련해 게임 모드에서 호출할 함수.
	void GameScoreChanged(int32 NewScore);
	void GameClear();
	void GameOver();
protected:
	virtual void BeginPlay() override;

protected:
	//생성할 위젯의 클래스 정보.
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = HUD)
		TSubclassOf<class UABHUDWidget> ABHUDWidgetClass;

	//생성할 위젯의 객체 정보를 저장할 변수
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = HUD)
		TObjectPtr<class UABHUDWidget>	ABHUDWidget;
};
