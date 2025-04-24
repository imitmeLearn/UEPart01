// Fill out your copyright notice in the Description page of Project Settings.

#include "GameData/ABGameSingleton.h"

DEFINE_LOG_CATEGORY(LogABGameSingleton);

UABGameSingleton::UABGameSingleton()
{
	//데이터 테이블 에셋 로드
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Game/ArenaBattle/GameData/ABCharacterStatTable.ABCharacterStatTable"));
	if(DataTableRef.Object)
	{
		//UDataTable 은 Key, Value 로 관리됨.
		//Map 으로 사용하지 않고, 배열로 직접 관리.
		const UDataTable* DataTable = DataTableRef.Object;

		//데이터 테이블이 제대로 초기화 되어 있는지,확인(검증)
		check(DataTable->GetRowMap().Num() > 0);

		//값 저장.을 위한 임시 배열.
		TArray<uint8*> ValueArray;	//데이블의 값 자료형이 uint8* 이기에!!!!! 사용함.

		//데이터 테이블의 GenerateValueArray  함수를 사용해 값 만 배열에 저장.
		DataTable->GetRowMap().GenerateValueArray(ValueArray);

		// Algo 알고리즘을 활용해 값을 변환해 저장.
		Algo::Transform(
			ValueArray
			,CharacterStatTable
			,[](uint8* Value){ return *reinterpret_cast<FABCharacterStat*>(Value);}
		);

		// Algo 알고리즘을 활용해 값을 변환해 저장. 대신 할 수 있는 for 문 사용 가능.
		//for (uint8* Value : ValueArray)
		//{
		//    CharacterStatTable.Add(*reinterpret_cast<FABCharacterStat*>(Value));
		//}
	}
	//최대 레벨 값 설정.
	CharacterMaxLevel = CharacterStatTable.Num();

	//값에 문제가 없는지 확인.
	ensure(CharacterMaxLevel>0);
}

UABGameSingleton & UABGameSingleton::Get()
{
	//싱글톤 가져오기(말안되는데, 언리얼에서 해주기에 가능한 부분)

	//프로젝트 세팅에 싱글톤으로 지정했기 때문에 가능.
	//Engine::Get() 이랑 비슷한거
	UABGameSingleton* Singleton =  Cast<UABGameSingleton>(GEngine->GameSingleton);

	//객체가 유효하면, 참조-레퍼런스로 변환.
	if(Singleton)
	{
		return *Singleton;
	}

	////도달하면 안되는 부분!
	//로그 찍어주기 -오류 출력
	UE_LOG(LogABGameSingleton,Error,TEXT("InValid Game Singleton."));

	//빈객체 반환
	return *NewObject<UABGameSingleton>();
}