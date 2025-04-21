// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/ABItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"

// Sets default values
AABItemBox::AABItemBox()
{
	//..컴포넌트 생성
	Trigger =CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect =CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	//..컴포넌트 계층 설정
	RootComponent = Trigger;
	Mesh -> SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	//..콜리전 프로파일 설정.
	Trigger -> SetCollisionProfileName(CPROFILE_ABTRIGGER);
	Mesh -> SetCollisionProfileName(TEXT("NoCollision"));

	//에셋 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Game/ArenaBattle/Environment/Props/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if(BoxMeshRef.Object)
	{
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}

	Mesh->AddRelativeLocation(FVector(0.f,-3.5f,-30.f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Game/ArenaBattle/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if(EffectRef.Object)
	{
		Effect->SetTemplate(EffectRef.Object);
		Effect->bAutoActivate = false;
	}
}