﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ABCharacterNonPlayer.h"
#include "Engine/AssetManager.h"

AABCharacterNonPlayer::AABCharacterNonPlayer()
{
	//메시 설정 안되어 있으니, 커놓고 시작!
	GetMesh()->SetHiddenInGame(true);
}

void AABCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	////메시 로드 요청
	//NPC Mehsed 목록 값이 제대로 설정됐는지 확인.
	ensure(NPCMeshes.Num()>0);
	//UE_LOG(LogTemp, Log, TEXT("NPCMeshes.Num(): %d"), NPCMeshes.Num());

	//랜덤으로 인덱스 선택
	int32 RandomIndex = FMath::RandRange(0,NPCMeshes.Num()-1);

	//비동기로 메시 요청.
	NPCMeshHandle =	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			NPCMeshes[RandomIndex]
			,FStreamableDelegate::CreateUObject(this,&AABCharacterNonPlayer::NPCMeshLoadCompleted)
	);
}

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	//타이머를 사용해 액터 제거.
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		DeadTimerHandle
		,FTimerDelegate::CreateLambda([&/*참조로 캡쳐?*/]()	{Destroy();	/*/액터 제거.*/	})
		,DeadEventDelayTime	//타이머 설정 시간.
		,false	//반복 여부 설정 (반복 안함)
	);
}

void AABCharacterNonPlayer::NPCMeshLoadCompleted()
{
	//메시 요청 시 반환된 핸들 값이 유효한지 확인.
	if(NPCMeshHandle.IsValid())
	{
		//로드된 에셋을 스캘레틸 메시 에셋으로 변환
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());

		//메시 에셋 설정.
		if(NPCMesh)
		{
			//스켈레탈 메시 에셋 설정.
			GetMesh()->SetSkeletalMesh(NPCMesh);

			//컴포넌트 보이도록 설정.
			GetMesh()->SetHiddenInGame(false);
		}
	}

	//에셋 로드에 사용했던 핸들 해제.
	NPCMeshHandle->ReleaseHandle();
}