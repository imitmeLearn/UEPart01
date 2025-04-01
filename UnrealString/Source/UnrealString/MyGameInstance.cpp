// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	//TCHAR Array
	TCHAR LogCharArray[] = TEXT("Hello Unreal");
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	//FString
	//std::string test; test.c_str();
	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);	//UE_LOG(LogTemp, Log, TEXT("%s"), LogCharString);	//error

	//FString -> TCHAR Array
	const TCHAR* LogCharPtr = *LogCharString;
	TCHAR* LogCharDataPtr = LogCharString.GetCharArray().GetData();

	//FString -> TCHAR Array copy
	TCHAR Buffer[100] = {};
	FCString::Strcpy(Buffer, LogCharString.Len(), *LogCharString);

	UE_LOG(LogTemp, Log, TEXT("%s"), Buffer);

	//Cut
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		//Get Index
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);

		//Cut
		FString EndString = LogCharString.Mid(Index);

		//Print
		UE_LOG(LogTemp, Log, TEXT("EndString: %s"), *EndString);
	}

	//Split
	//strtoc_s.
	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right))
	{
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s 와 %s"), *Left, *Right);
	}

	//sprintf_s.
	int32 IntValue = 32;
	float FloatValue = 3.141592f;
	FString FloatIntString = FString::Printf(TEXT("sprintf_s : Int: %d, Float: %f"), IntValue, FloatValue);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);

	//숫자 ->문자
	FString IntString = FString::FromInt(IntValue);
	FString FloatString = FString::SanitizeFloat(FloatValue);
	UE_LOG(LogTemp, Log, TEXT("숫자 ->문자 : Int: %s, Float: %s"), *IntString, *FloatString);

	//문자 ->숫자
	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	UE_LOG(LogTemp, Log, TEXT("문자 ->숫자 : Int: %d, Float: %f"), IntValueFromString, FloatValueFromString);

	//FName의 특징
	FName Key1(TEXT("TEST"));
	FName Key2(TEXT("test"));

	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s")
		, (Key1 == Key2 ? TEXT("같음") : TEXT("다름~")));
}