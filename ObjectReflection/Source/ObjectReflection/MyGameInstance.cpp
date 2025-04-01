// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	//기본값 설정.
	//CDO(Class Default Object)
	//템플릿 클래스 객체
	SchoolName = TEXT("원티드 스클");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("======================================="));
	//클래스 정보 가져오기.
	UClass* RuntimeClass = GetClass();
	UClass* StaticClass = UMyGameInstance::StaticClass();
	//어써트 Assert : 무조건 확인되고, 다음코드 실행되어야 할떄, 검증되어야 할떄, 개발과정에서 사용하는것,-> 릴리즈 시 없어짐.
	//check(RuntimeClass == StaticClass);
	//check(RuntimeClass != StaticClass);	//일부로 오류내보기. //통과 해야 하는 조건을 넣어줘야 한다.

	//ensure(RuntimeClass != StaticClass); //check처럼 꺼지진 않지만, 오류 위치 알려줌.
	ensure(RuntimeClass == StaticClass); //같아야 통과
	//ensureMsgf(RuntimeClass != StaticClass, TEXT("일부로 오류 발생시켜봄.")); //같아야 통과

	UE_LOG(LogTemp, Log, TEXT("학교 담당 클래스 이름 : %s"), *RuntimeClass->GetName());

	SchoolName = TEXT("새로 변경된 학교");
	UE_LOG(LogTemp, Log, TEXT("학교이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교이름 기본값 : %s"),
		*RuntimeClass->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("======================================="));
}