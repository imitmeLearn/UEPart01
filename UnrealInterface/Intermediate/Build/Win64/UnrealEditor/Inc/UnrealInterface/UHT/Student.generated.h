// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Student.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UNREALINTERFACE_Student_generated_h
#error "Student.generated.h already included, missing '#pragma once' in Student.h"
#endif
#define UNREALINTERFACE_Student_generated_h

#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUStudent(); \
	friend struct Z_Construct_UClass_UStudent_Statics; \
public: \
	DECLARE_CLASS(UStudent, UPerson, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/UnrealInterface"), NO_API) \
	DECLARE_SERIALIZER(UStudent) \
	virtual UObject* _getUObject() const override { return const_cast<UStudent*>(this); }


#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UStudent(UStudent&&); \
	UStudent(const UStudent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UStudent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UStudent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UStudent) \
	NO_API virtual ~UStudent();


#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h_15_PROLOG
#define FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h_18_INCLASS_NO_PURE_DECLS \
	FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> UNREALINTERFACE_API UClass* StaticClass<class UStudent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Workspace_UnrealProjects_UEPart01_UnrealInterface_Source_UnrealInterface_Student_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
