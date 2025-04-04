// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

//이름을 랜덤으로 생성해주는 함수. //해더에 하지 않는이유는 공개하는 것 아니고, cpp 내부에서만 사용될 것이기에.
FString  MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박이");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	//TCAHR 초기값안넣으면, 할당기본크기.?? 공간확보 안해, 명시적으로 지정하지 않으면,
	TArray<TCHAR> RandArray; //랜덤이름 생성을 위한 배열
	RandArray.SetNum(3);	//초기 크기 확보
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandArray.GetData();
}

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

	UE_LOG(LogTemp, Log, TEXT("==	//조건 설정해서, 삭제 return Val/2 == 0===="));
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

	UE_LOG(LogTemp, Log, TEXT("=====TSet======="));
	TSet<int32> IntSet;	//TArray
	for (int ix = 0; ix < 10; ix++)
	{
		IntSet.Add(ix + 1);
	}	//동적 배열에 자료 추가.

	IntSet.Remove(2);

	StudentData.Add(FStudentData(1, TEXT("장세윤"))); //구조체 입력 예시,

	UE_LOG(LogTemp, Log, TEXT("====학생 데이터 생성===="));
	const int32 StudentCount = 300;
	for (int32 ix = 0; ix < StudentCount; ix++)
	{
		//배열을 순회하면서, 랜덤으로 이름을 생성 후 배열에 추가.
		StudentData.Emplace(FStudentData(ix + 1, MakeRandomName()));
	}

	UE_LOG(LogTemp, Log, TEXT("===//학생 데이터를 TArray 로 변환.==="));
	TArray<FString> AllStudentNames;
	Algo::Transform(StudentData
		, AllStudentNames
		, [](const FStudentData& Val)	//람다
	{
		return Val.Name;
	}
	);
	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentNames.Num());

	UE_LOG(LogTemp, Log, TEXT("====학생 데이터 를 TSet으로 변환===="));

	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentData
		, AllUniqueNames
		, [](const FStudentData& Val)	//람다
	{
		return Val.Name;
	}
	);
	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수 : %d"), AllUniqueNames.Num());

	UE_LOG(LogTemp, Log, TEXT("====학생 데이터 를 Map으로 변환(중복 포함)===="));
	Algo::Transform(StudentData
		, StudentMap
		, [](const FStudentData& Val)	//람다
	{
		return TPair<int32, FString>(Val.Order, Val.Name);//이름 중보되지 않고 나옴.
	}
	);
	UE_LOG(LogTemp, Log, TEXT(" 학생 이름의 수 : %d"), StudentMap.Num());

	UE_LOG(LogTemp, Log, TEXT("====학생 데이터 를 Map으로 변환(중복 제거)===="));
	TMap<FString, int32> StudentMapByName;
	Algo::Transform(StudentData
		, StudentMapByName
		, [](const FStudentData& Val)	//람다
	{
		return TPair< FString, int32>(Val.Name, Val.Order);
	}
	);
	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수 : %d"), StudentMapByName.Num());
}