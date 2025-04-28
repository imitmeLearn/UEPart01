// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "Interface/ABCharacterAIInterface.h"
#include "ABCharacterNonPlayer.generated.h"

/**
 *
 */
UCLASS(config=ArenaBattle)
class ARENABATTLEDEMO_API AABCharacterNonPlayer: public AABCharacterBase
	,public IABCharacterAIInterface
{
	GENERATED_BODY()
public:
	AABCharacterNonPlayer();

protected:
	//랜덤으로 매시 로드 요청을 위한 함수.
	virtual void PostInitializeComponents() override;

	virtual void SetDead() override;

	//npc 매시 로드 완료될 떄, 호출될 콜백.
	void NPCMeshLoadCompleted();

	//config 파일에 저장된 경로 값을 배열로 관리.
	UPROPERTY(config)
		TArray<FSoftObjectPath> NPCMeshes;

	//배열 채워진 경로를 활용해 비동기로 에셋을 로드할 때 사용.
	TSharedPtr<FStreamableHandle> NPCMeshHandle;

protected:	//AI SECTION
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttactRange() override;
	virtual float GetAITurnSpeed() override;
};
