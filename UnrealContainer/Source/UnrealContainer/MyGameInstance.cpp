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

	UE_LOG(LogTemp, Log, TEXT("======================="));

	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT(" 배열 값 : %d"), Item);	//출력
	}

	UE_LOG(LogTemp, Log, TEXT("==	//조건 설정해서, 삭제 return Val % 2 == 0===="));
	IntArray.RemoveAll([](int32 Val) {return Val % 2 == 0; });
	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT(" 배열 값 : %d"), Item);	//출력
	}

	UE_LOG(LogTemp, Log, TEXT("=====IntArray += {2, 4, 6, 8, 10};=========="));

	IntArray += {2, 4, 6, 8, 10};
	for (const auto& Item : IntArray)
	{
		UE_LOG(LogTemp, Log, TEXT(" 배열 값 : %d"), Item);
	}

	UE_LOG(LogTemp, Log, TEXT("=====배열 통복사 =========="));
	int CArray[10];
	FMemory::Memcpy(CArray, IntArray.GetData(), sizeof(int32) * IntArray.Num());
	for (const auto& Item : CArray)
	{
		UE_LOG(LogTemp, Log, TEXT(" Item : %d"), Item);	//출력
	}

	UE_LOG(LogTemp, Log, TEXT("=====합계========="));
	int32 SumByAlgo = Algo::Accumulate(IntArray, 0);
	UE_LOG(LogTemp, Log, TEXT("SumByAlgo: %d "), SumByAlgo);	//출력
}