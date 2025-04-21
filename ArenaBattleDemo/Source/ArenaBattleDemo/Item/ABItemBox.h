// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLEDEMO_API AABItemBox: public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	// 액터의 충돌을 담당할 박스 컴포넌트.
	UPROPERTY(VisibleAnywhere,Category = Box)
		TObjectPtr<class UBoxComponent> Trigger;

	// 아이템 박스를 보여줄 메시 컴포넌트.
	UPROPERTY(VisibleAnywhere,Category = Box)
		TObjectPtr<class UStaticMeshComponent> Mesh;

	// 박스와 상호작용했을 때 보여줄 파티클 효과 컴포넌트.
	UPROPERTY(VisibleAnywhere,Category = Box)
		TObjectPtr<class UParticleSystemComponent> Effect;
public:
};
