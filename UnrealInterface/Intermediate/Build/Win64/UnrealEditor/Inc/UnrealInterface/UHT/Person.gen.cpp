// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealInterface/Person.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePerson() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UNREALINTERFACE_API UClass* Z_Construct_UClass_UPerson();
UNREALINTERFACE_API UClass* Z_Construct_UClass_UPerson_NoRegister();
UPackage* Z_Construct_UPackage__Script_UnrealInterface();
// End Cross Module References

// Begin Class UPerson Function DoLesson
struct Z_Construct_UFunction_UPerson_DoLesson_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Person.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPerson_DoLesson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UPerson, nullptr, "DoLesson", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPerson_DoLesson_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPerson_DoLesson_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UPerson_DoLesson()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPerson_DoLesson_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPerson::execDoLesson)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLesson();
	P_NATIVE_END;
}
// End Class UPerson Function DoLesson

// Begin Class UPerson
void UPerson::StaticRegisterNativesUPerson()
{
	UClass* Class = UPerson::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "DoLesson", &UPerson::execDoLesson },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPerson);
UClass* Z_Construct_UClass_UPerson_NoRegister()
{
	return UPerson::StaticClass();
}
struct Z_Construct_UClass_UPerson_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "IncludePath", "Person.h" },
		{ "ModuleRelativePath", "Person.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xec\x96\xb8\xeb\xa6\xac\xec\x96\xbc\xec\x9d\x98 \xea\xb4\x80\xeb\xa6\xac\xeb\xa5\xbc \xeb\xb0\x9b\xeb\x8f\x84\xeb\xa1\x9d!\n" },
#endif
		{ "ModuleRelativePath", "Person.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x96\xb8\xeb\xa6\xac\xec\x96\xbc\xec\x9d\x98 \xea\xb4\x80\xeb\xa6\xac\xeb\xa5\xbc \xeb\xb0\x9b\xeb\x8f\x84\xeb\xa1\x9d!" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Year_MetaData[] = {
		{ "ModuleRelativePath", "Person.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Year;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UPerson_DoLesson, "DoLesson" }, // 1850404832
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPerson>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UPerson_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPerson, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UPerson_Statics::NewProp_Year = { "Year", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPerson, Year), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Year_MetaData), NewProp_Year_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPerson_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPerson_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPerson_Statics::NewProp_Year,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPerson_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_UnrealInterface,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPerson_Statics::ClassParams = {
	&UPerson::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UPerson_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams), Z_Construct_UClass_UPerson_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPerson()
{
	if (!Z_Registration_Info_UClass_UPerson.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPerson.OuterSingleton, Z_Construct_UClass_UPerson_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPerson.OuterSingleton;
}
template<> UNREALINTERFACE_API UClass* StaticClass<UPerson>()
{
	return UPerson::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPerson);
UPerson::~UPerson() {}
// End Class UPerson

// Begin Registration
struct Z_CompiledInDeferFile_FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPerson, UPerson::StaticClass, TEXT("UPerson"), &Z_Registration_Info_UClass_UPerson, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPerson), 1249388156U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_1858194784(TEXT("/Script/UnrealInterface"),
	Z_CompiledInDeferFile_FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
