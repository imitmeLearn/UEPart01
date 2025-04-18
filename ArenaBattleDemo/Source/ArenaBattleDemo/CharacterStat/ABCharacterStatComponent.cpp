// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterStatComponent.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	MaxHp = 200.f;
	CurrentHp = MaxHp;
}

// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);	//게임 시작되면, 체력 가득 채우기.
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PreHP = CurrentHp;	//데이미 처리
	const float ActualDamage = FMath::Clamp<float>(InDamage,0.f,InDamage);	//데미지 보정 값.	//(방어구 등)로 인해 음수 일 수 있오, 음수인 경우 0 설정.

	//CurrentHp = FMath::Clamp<float> (PreHP - ActualDamage,0.f,MaxHp);			//데미지 계산
	SetHp(PreHP - ActualDamage);	//데미지 계산

	if(CurrentHp <= KINDA_SMALL_NUMBER)	//죽었는지 (체력 모두 솝했는지)확인
	{
		OnHpZero .Broadcast();	//이벤트 발행
	}
	return ActualDamage;
}

void UABCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float> (NewHp,0.f,MaxHp);			//현재 체력 업데이트
	OnHpChanged.Broadcast(CurrentHp);	 //체력 변경이벤트 발행
}