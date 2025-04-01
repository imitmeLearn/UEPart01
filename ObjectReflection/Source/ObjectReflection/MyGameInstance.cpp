// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"
#include "Student.h"
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

	UE_LOG(LogTemp, Log, TEXT("======================================="));
	//클래스 정보 가져오기.
	UClass* RuntimeClass = GetClass();
	UClass* StaticClass = UMyGameInstance::StaticClass();
	//어써트 Assert : 무조건 확인되고, 다음코드 실행되어야 할떄, 검증되어야 할떄, 개발과정에서 사용하는것,-> 릴리즈 시 없어짐.
	//check(RuntimeClass == StaticClass);
	//check(RuntimeClass != StaticClass);	//일부로 오류내보기. //통과 해야 하는 조건을 넣어줘야 한다.

	//ensure(RuntimeClass != StaticClass); //check처럼 꺼지진 않지만, 오류 위치 알려줌.
	//ensureMsgf(RuntimeClass != StaticClass, TEXT("일부로 오류 발생시켜봄.")); //같아야 통과
	//ensureMsgf(RuntimeClass == StaticClass, TEXT("True 인데, 실행되나??????")); //동과되나봐,  안나옴.
	ensure(RuntimeClass == StaticClass); //같아야 통과 //한줄로 해결 가능.

	UE_LOG(LogTemp, Log, TEXT("학교 담당 클래스 이름 : %s"), *RuntimeClass->GetName());

	SchoolName = TEXT("새로 변경된 학교");
	UE_LOG(LogTemp, Log, TEXT("학교이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교이름 기본값 : %s"),
		*RuntimeClass->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("======================================="));

	//student /Teacher 객체 생성
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 : %s"),
		*Student->GetName()
	);

	//리플랙션을 이용한 프로퍼티 정보 설정
	UE_LOG(LogTemp, Log, TEXT("====리플랙션을 이용한 프로퍼티 정보 설정====="));

	FProperty* NameProperty
		= UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));

	//현재 저장된 값 가져오기
	FString CurrnetTeacherName;
	if (NameProperty)
	{
		NameProperty->GetValue_InContainer(Teacher, &CurrnetTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 : %s"),
			*CurrnetTeacherName
		);

		FString NewTeacherName(TEXT("장세윤"));
		NameProperty->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 : %s"),
			*Teacher->GetName()
		);
	}

	UE_LOG(LogTemp, Log, TEXT("======================================="));

	UE_LOG(LogTemp, Log, TEXT("=====직접호출 , 리플랙션을 통한 함수 호출======"));
	Student->DoLesson();		//제일 빠른 형태 //직접호출
	//리플랙션을 통한 함수 호출
	UFunction* DoLessonFuntion = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFuntion)
	{
		Teacher->ProcessEvent(DoLessonFuntion, nullptr);
	}
	UE_LOG(LogTemp, Log, TEXT("======================================="));
}