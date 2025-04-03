// Fill out your copyright notice in the Description page of Project Settings.

#include "Teacher.h"
#include "Student.h"
#include "Staff.h"
#include "MyGameInstance.h"
#include "Card.h"
#include "CourseInfo.h"

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
	{
		UE_LOG(LogTemp, Log, TEXT("==// 학사 정보 객체 생성.====="));

		// 학사 정보 객체 생성.
		CourseInfo = NewObject<UCourseInfo>(this);

		// 학생 객체 생성.
		UStudent* Student1 = NewObject<UStudent>();
		Student1->SetName(TEXT("학생1"));

		UStudent* Student2 = NewObject<UStudent>();
		Student2->SetName(TEXT("학생2"));

		UStudent* Student3 = NewObject<UStudent>();
		Student3->SetName(TEXT("학생3"));

		// 구독할 함수 등록.
		CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
		CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
		CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

		// 발행.
		CourseInfo->ChangeCourseInfo(SchoolName, TEXT("새로운 학사 정보"));

		UE_LOG(LogTemp, Log, TEXT("======================="));
	}

	{
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
			UE_LOG(LogTemp, Log, TEXT("===	//인터페이스 구현 여부 확인===="));

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

			//카드 정보 출력
			UE_LOG(LogTemp, Log, TEXT("==카드 정보 출력==="));
			const UCard* OwnCard = Person->GetCard();
			//check(OwnCard);
			ensure(OwnCard);

			//문자열로 출력
			const UEnum* CardEnumType
				= FindObject<UEnum>(nullptr
					, TEXT("/Script/UnrealComposition.ECardType"));

			if (CardEnumType)
			{
				FString CardMetaData =
					CardEnumType->GetDisplayNameTextByValue
					((int64)OwnCard->GetCardType()).ToString();
				;

				UE_LOG(LogTemp, Log, TEXT("%s 님이 소유한 카드 종류 : %d")
					, *Person->GetName()
					, OwnCard->GetCardType()
				);
			}
		}

		UE_LOG(LogTemp, Log, TEXT("========================"));

		FName key1(TEXT("TEST"));
		FName key2(TEXT("test"));
		UE_LOG(LogTemp, Log, TEXT("결과 :%s"), (key1 == key2 ? TEXT("same") : TEXT("Dif")));

		//UE_LOG(LogTemp, Log, TEXT("key1 :%s"), TEXT("TEST"));
		//UE_LOG(LogTemp, Log, TEXT("key1 :%s"), FName key3(TEXT("TEST")));
		//UE_LOG(LogTemp, Log, TEXT("key1 :%s"), *key1);
		//UE_LOG(LogTemp, Log, TEXT("key1 :%s"), &key1);
		//UE_LOG(LogTemp, Log, TEXT("key1 :%s"), key1);
		//UE_LOG(LogTemp, Log, TEXT("key2 :%s"), (key2));
		//UE_LOG(LogTemp, Log, TEXT("key2 :%s"), *key2);
		//UE_LOG(LogTemp, Log, TEXT("key2 :%s"), key2);
		UE_LOG(LogTemp, Log, TEXT("key1 :%s"), *key1.ToString()); //FName 타입을 문자열로 출력하기 위해서는 ToString() 메서드를 사용해야 하고,  포인터 연산자 *를 사용하여 TCHAR* 타입으로 변환해야 한다.
		UE_LOG(LogTemp, Log, TEXT("key2 :%s"), *key2.ToString()); //FName 타입을 문자열로 출력하기 위해서는 ToString() 메서드를 사용해야 하고,  포인터 연산자 *를 사용하여 TCHAR* 타입으로 변환해야 한다.
	}
}