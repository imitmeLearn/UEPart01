// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"

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
			UE_LOG(LogTemp, Log, TEXT("이름: %s, 순번 %d")
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
	}
}