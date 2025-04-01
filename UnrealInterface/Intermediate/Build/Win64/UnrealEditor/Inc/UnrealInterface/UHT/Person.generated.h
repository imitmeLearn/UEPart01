// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Person.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UNREALINTERFACE_Person_generated_h
#error "Person.generated.h already included, missing '#pragma once' in Person.h"
#endif
#define UNREALINTERFACE_Person_generated_h

#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPerson(); \
	friend struct Z_Construct_UClass_UPerson_Statics; \
public: \
	DECLARE_CLASS(UPerson, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/UnrealInterface"), NO_API) \
	DECLARE_SERIALIZER(UPerson)


#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPerson(UPerson&&); \
	UPerson(const UPerson&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPerson); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPerson); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPerson) \
	NO_API virtual ~UPerson();


#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_12_PROLOG
#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_15_INCLASS_NO_PURE_DECLS \
	FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> UNREALINTERFACE_API UClass* StaticClass<class UPerson>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Person_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
