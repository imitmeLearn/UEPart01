// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"
UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();
	//데이터 생성
	FStudentData RawDataSource(31, TEXT("장세윤"));
	//경로.
	const FString SavedPath = FPaths::Combine(
		FPlatformMisc::ProjectDir()
		, TEXT("Saved")
	);

	//테스트 출력
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 : %s"), *SavedPath);
	{
		//파일 이름.
		const FString RawDataFileName(TEXT("RawData.Bin"));
		//절대 경로 설정 후, 절대 경로로 변경
		FString RawDataAbsolutePath = FPaths::Combine(SavedPath, RawDataFileName);

		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로: %s"), *RawDataAbsolutePath);

		//절대 경로로  변경
		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 경로: %s"), *RawDataAbsolutePath);

		//구조체 데이터 직렬화
		FArchive* RawFileWriteAr = IFileManager::Get().CreateDebugFileWriter(
			*RawDataAbsolutePath
		);

		if (RawFileWriteAr)
		{
			//데이터 넣기
			//*RawFileWriteAr << RawDataSource.Order;
			//*RawFileWriteAr << RawDataSource.Name;
			*RawFileWriteAr << RawDataSource;

			//아카이브 닫기
			RawFileWriteAr->Close();

			//메모리 해제
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;
		}

		//역질렬화 (읽기).
		FStudentData RawDataDeserialized;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(
			*RawDataAbsolutePath
		);

		if (RawFileReaderAr)
		{
			//데이터 읽기
			//*RawFileReaderAr << RawDataDeserialized.Order;
			//*RawFileReaderAr << RawDataDeserialized.Name;
			*RawFileReaderAr << RawDataDeserialized;

			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			//출력
			UE_LOG(LogTemp, Log, TEXT("[RawData]이름: %s, 순번 %d")
				, *RawDataDeserialized.Name
				, RawDataDeserialized.Order
			);
		}
	}

	//UObject 직렬화.
	StudentSource = NewObject<UStudent>();
	StudentSource->SetOrder(40);
	StudentSource->SetName(TEXT("장세윤"));
	{
		//파일 이름
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));

		//폴더 경로
		FString ObjectDataAbsolutePath = FPaths::Combine(
			*SavedPath
			, *ObjectDataFileName
		);

		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		//직렬화
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSource->Serialize(MemoryWriterAr);

		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(
			IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)
		))
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}
		//역직렬화
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(
			IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)
		))
		{
			TArray<uint8> BufferArrayFromFile;
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();

			FMemoryReader MemoryReaderAr(BufferArrayFromFile);
			UStudent* StudentDes = NewObject<UStudent>();
			StudentDes->Serialize(MemoryReaderAr);

			UE_LOG(LogTemp, Log, TEXT("이름: %s, 순번 %d")
				, *StudentDes->GetName()
				, StudentDes->GetOrder()
			);
		}
	}

	//JSON 직렬화
	const FString JsonDataFileName(TEXT("StudentJsonData.json"));

	//경로
	FString JsonDataAbsolutePath = FPaths::Combine(*SavedPath, *JsonDataFileName);
	FPaths::MakeStandardFilename(JsonDataAbsolutePath);

	//Json 객체 생성
	TSharedRef<FJsonObject> JsonObjectSource = MakeShared<FJsonObject>();

	//UObject -> Json 객체 변환
	FJsonObjectConverter::UStructToJsonObject(
		StudentSource->GetClass()
		, StudentSource
		, JsonObjectSource
	);
	//Json 객체 -> //Json  문자열
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr
		= TJsonWriterFactory<TCHAR>::Create(&JsonString);

	//Json 문자열에 직렬화 진행
	if (FJsonSerializer::Serialize(JsonObjectSource, JsonWriterAr))
	{
		//파일에 저장.
		FFileHelper::SaveStringToFile(JsonString, *JsonDataAbsolutePath);
	}

	//직렬화 태그 잘해주면, 직렬화로 열며...

	//Json Read.
	FString JsonFromFile;
	FFileHelper::LoadFileToString(JsonFromFile, *JsonDataAbsolutePath);

	//Json String -> Json Object
	TSharedRef<TJsonReader<TCHAR>> JsonReaderAr
		= TJsonReaderFactory<TCHAR>::Create(JsonFromFile);
	TSharedPtr<FJsonObject> JsonObjectResult;
	if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectResult))
	{
		//Josn Object->UObject
		UStudent* JsonStudent = NewObject<UStudent>();
		if (FJsonObjectConverter::JsonObjectToUStruct(
			JsonObjectResult.ToSharedRef()
			, JsonStudent->GetClass()
			, JsonStudent
		))
		{
			//TestPrint
			UE_LOG(LogTemp, Log, TEXT("[JsonData] 이름: %s, 순번 %d")
				, *JsonStudent->GetName()
				, JsonStudent->GetOrder()
			);
		}
	}
	//패키지 저장 함수 호출.
	UE_LOG(LogTemp, Log, TEXT("<패키지 저장 호출.>"));
	SaveStudentPackage();

	//패키기 에셋 로드 함수 호출.
	UE_LOG(LogTemp, Log, TEXT("<패키지 에셋 로드 호출.>"));
	LoadStudentPackage();

	//비동기 에셋 로드
	//비동기 처리 시, 끝났는지 확인을 위한, 콜백(Callback)함수가 꼭! 필요하다!
	///Script/UnrealSerialization.Student'/Game/Student.Student'
	UE_LOG(LogTemp, Log, TEXT("<비동기 에셋 로드 호출.>"));
	FString ObjectPath = FString::Printf(
		TEXT("%s.%s")
		, TEXT("/Game/Student")	//패키지 정보
		, TEXT("Student")	//에셋 정보
	);

	Handle = StreamableManager.RequestAsyncLoad(
		ObjectPath	//경로
		, [&]()	//참조 콜백 // 콜백 람다 씀. // 캡쳐한 줄
	{
		//값 출력
		UStudent* Student = Cast<UStudent>(Handle->GetLoadedAsset());
		if (Student)
		{
			UE_LOG(LogTemp, Log, TEXT("[AsyncLoad] 이름: %s, 순번 %d")
				, *Student->GetName()
				, Student->GetOrder()
			);
		}

		//핸들 해제
		Handle->ReleaseHandle();
		Handle.Reset();
	}	//,[](){}
	);
}

void UMyGameInstance::SaveStudentPackage()
{
	//에셋 저장하기 전에 완전히 로드되도록 처리.
	//ㄴ저장하려고 시도할때, 패키지 만들다 오류나는것이기에,  사전에 완전히 로드되도록 처리해줘야 한다.
	UPackage* StudentPackage = LoadPackage(nullptr, TEXT("/Game/Student"), LOAD_None);
	if (StudentPackage) {
		StudentPackage->FullyLoad();
	}

	//패키지 만들고,
	StudentPackage = CreatePackage(TEXT("/Game/Student"));
	////패키지 구성을 위한 플래그 지정.
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	//UObject 만들고,
	UStudent* TopStudent = NewObject<UStudent>(
		StudentPackage
		, UStudent::StaticClass()
		, TEXT("Student") //패키지 이름과 맞춰줘야 에디터에 나온다
		, ObjectFlag
	);

	//패키지에 UObject 넣기!
	////값 설정
	TopStudent->SetOrder(40);
	TopStudent->SetName(TEXT("장세윤"));

	//패키지 저장
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(
		TEXT("/Game/Student")
		, FPackageName::GetAssetPackageExtension()
	);

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;
	if (UPackage::SavePackage(
		StudentPackage
		, nullptr
		, *PackageFileName
		, SaveArgs
	))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지 성공적으로 저장됨."));
	}
}

void UMyGameInstance::LoadStudentPackage()
{
	//패키지 경로 설정
	UPackage* StudentPackage = LoadPackage(
		nullptr
		, TEXT("/Game/Student")
		, LOAD_None
	);

	//패키지 로드 실패.
	if (!StudentPackage) {
		UE_LOG(LogTemp, Log, TEXT("패키지 찾을 수 없음."));
		return;
	}

	//패키지 완전히 로드 처리
	StudentPackage->FullyLoad();

	//에셋 로드
	UStudent* Student = FindObject<UStudent>(StudentPackage, TEXT("Student"));
	if (Student)
	{
		UE_LOG(LogTemp, Log, TEXT("[FindObject Asset] 이름: %s, 순번 %d")
			, *Student->GetName()
			, Student->GetOrder()
		);
	}
}