// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/ABItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/ABCollision.h"

#include "Interface/ABCharacterItemInterface.h"

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

	//박스의 크기 조정
	Trigger->SetBoxExtent(FVector(40.f,42.f,30.f));

	//트리거 발생하는 다이나믹 델리게이트에 함수 등록.
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&AABItemBox::OnOverlapBegin);

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
		//파티클 에셋 설정
		Effect->SetTemplate(EffectRef.Object);
		//바로 재생되지 않도록 설정.
		Effect->bAutoActivate = false;
	}

	//Trigger->OnComponentBeginOverlap
	//Effect -> OnSystemFinished
}

void AABItemBox::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent,AActor * OtherActor,UPrimitiveComponent * OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult & SweepResult)
{
	//아이템이 널이면, 꽝
	if(!Item)
	{
		Destroy();
		return;
	}
	//아이템 있으면, 캐럭터에 아이템 획득 메시지 전달.
	IABCharacterItemInterface* OverlappedPawn = Cast<IABCharacterItemInterface>(OtherActor);

	//부딪힌 문체가,
	if(OverlappedPawn)
	{
		OverlappedPawn->TakeItem(Item);
	}

	//파티클 재생.
	Effect->Activate();

	//메시는 안보이도록 처리(비활성화)
	Mesh -> SetHiddenInGame(true);

	//엑터의 콜리전 끄기.
	SetActorEnableCollision(false);

	//파티클 재생 종료시 발행되는 델리게이트에 함수 등록.
	Effect->OnSystemFinished.AddDynamic(this,&AABItemBox::OnEffectFinished);
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	//파티클 재생이 완료되면, 액터 삭제
	Destroy();
}