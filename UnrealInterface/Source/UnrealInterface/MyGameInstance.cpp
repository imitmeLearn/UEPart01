﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	//기본값 설정.
	//CDO(Class Default Object)
	//템플릿 클래스 객체
	SchoolName = TEXT("엔진 켜진상태에서 변경 스클"); //엔진 초기화 과정에서 CDO 설정되기에, CDO 가 바뀌면, 껐다가 다시 켜야 한다. 라이브코딩에선 안된다.
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("===	//객체 생성===="));

	//동적배열 TArray 템플릿 지정된.
	TArray<UPerson*>Persons =
	{
		NewObject<UStudent>()
		,NewObject<UTeacher>()
		,NewObject<UStaff>()
	};

	UE_LOG(LogTemp, Log, TEXT("===//이름 출력===="));

	for (const auto Person : Persons)
	{
		//인터페이스 구현 여부 확인
		ILessonInterface* LessonInterface
			= Cast<ILessonInterface>(Person);

		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("참여가능 : %s"), *Person->GetName());
			LessonInterface->DoLesson();
		}

		else
		{
			UE_LOG(LogTemp, Log, TEXT("참여 불가능 : %s"), *Person->GetName());
		}

		Person->GetName();
		UE_LOG(LogTemp, Log, TEXT("구성원 이름 : %s"), *Person->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("========================"));
}