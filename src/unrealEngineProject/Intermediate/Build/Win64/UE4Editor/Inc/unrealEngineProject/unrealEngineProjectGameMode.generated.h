// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UNREALENGINEPROJECT_unrealEngineProjectGameMode_generated_h
#error "unrealEngineProjectGameMode.generated.h already included, missing '#pragma once' in unrealEngineProjectGameMode.h"
#endif
#define UNREALENGINEPROJECT_unrealEngineProjectGameMode_generated_h

#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_RPC_WRAPPERS
#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAunrealEngineProjectGameMode(); \
	friend UNREALENGINEPROJECT_API class UClass* Z_Construct_UClass_AunrealEngineProjectGameMode(); \
	public: \
	DECLARE_CLASS(AunrealEngineProjectGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, unrealEngineProject, NO_API) \
	DECLARE_SERIALIZER(AunrealEngineProjectGameMode) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AunrealEngineProjectGameMode*>(this); }


#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_INCLASS \
	private: \
	static void StaticRegisterNativesAunrealEngineProjectGameMode(); \
	friend UNREALENGINEPROJECT_API class UClass* Z_Construct_UClass_AunrealEngineProjectGameMode(); \
	public: \
	DECLARE_CLASS(AunrealEngineProjectGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, unrealEngineProject, NO_API) \
	DECLARE_SERIALIZER(AunrealEngineProjectGameMode) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AunrealEngineProjectGameMode*>(this); }


#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AunrealEngineProjectGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AunrealEngineProjectGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AunrealEngineProjectGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AunrealEngineProjectGameMode); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AunrealEngineProjectGameMode(const AunrealEngineProjectGameMode& InCopy); \
public:


#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AunrealEngineProjectGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AunrealEngineProjectGameMode(const AunrealEngineProjectGameMode& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AunrealEngineProjectGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AunrealEngineProjectGameMode); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AunrealEngineProjectGameMode)


#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_11_PROLOG
#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_RPC_WRAPPERS \
	unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_INCLASS \
	unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_POP


#define unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_INCLASS_NO_PURE_DECLS \
	unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_POP


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID unrealEngineProject_Source_unrealEngineProject_unrealEngineProjectGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS