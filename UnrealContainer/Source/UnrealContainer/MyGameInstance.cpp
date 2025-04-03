// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TArray<int32> IntArray;	//TArray
	for (int ix = 0; ix < 10; ix++)
	{
		IntArray.Add(ix + 1);
	}	//동적 배열에 자료 추가.

	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT(" 배열 값 : % d"), Item);
	}
}