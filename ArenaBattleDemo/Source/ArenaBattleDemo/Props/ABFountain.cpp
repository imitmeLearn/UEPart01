// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ABFountain.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AABFountain::AABFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ����
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	// �⺻ �����ʺz�� Body ������Ʈ�� ����
	RootComponent = Body;

	// Water ������Ʈ�� Body�� ���� �������� ����
	Water->SetupAttachment(Body);
	// ������ ��ġ�� ����
	Water->SetRelativeLocation(FVector(0.f, 0.f, 135.f));

	// ���� �˻�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FountainBodyMesh(TEXT("/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));

	// ���ҽ� ����
	if (FountainBodyMesh.Object)
	{
		Body->SetStaticMesh(FountainBodyMesh.Object);
	}

	// ���� �˻�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FountainWaterMesh(TEXT("/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));

	// ���ҽ� ����
	if (FountainWaterMesh.Object)
	{
		Water->SetStaticMesh(FountainWaterMesh.Object);
	}
}

// Called when the game starts or when spawned
void AABFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

