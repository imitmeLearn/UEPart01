// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"

#include "ABCharacterPlayer.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLEDEMO_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterPlayer();
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; //입력 바인딩 하는 함수

	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UABCharacterControlData* InCharacterControlData) override;

protected:
	void ChangeCharacterControl();
	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void QuarterMove(const FInputActionValue& Value);
	void QuarterLook(const FInputActionValue& Value);
	void QuarterMove_mujisung(const FInputActionValue& Value);
	//void Jump(const FInputActionValue& Value);	//이건 언리얼에서 제공하는 걸로 할거임.

	//Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	//Iput Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuarterMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuarterLookAction;

	ECharacterControlType CurrentCharacterControlType; //현재 사용중인 캐릭터 모드.
};
