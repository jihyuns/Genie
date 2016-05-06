// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UNREALENGINEPROJECT_GenieCharacter_generated_h
#error "GenieCharacter.generated.h already included, missing '#pragma once' in GenieCharacter.h"
#endif
#define UNREALENGINEPROJECT_GenieCharacter_generated_h

#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_RPC_WRAPPERS
#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_RPC_WRAPPERS_NO_PURE_DECLS
#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAGenieCharacter(); \
	friend UNREALENGINEPROJECT_API class UClass* Z_Construct_UClass_AGenieCharacter(); \
	public: \
	DECLARE_CLASS(AGenieCharacter, APawn, COMPILED_IN_FLAGS(0), 0, unrealEngineProject, NO_API) \
	DECLARE_SERIALIZER(AGenieCharacter) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AGenieCharacter*>(this); }


#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_INCLASS \
	private: \
	static void StaticRegisterNativesAGenieCharacter(); \
	friend UNREALENGINEPROJECT_API class UClass* Z_Construct_UClass_AGenieCharacter(); \
	public: \
	DECLARE_CLASS(AGenieCharacter, APawn, COMPILED_IN_FLAGS(0), 0, unrealEngineProject, NO_API) \
	DECLARE_SERIALIZER(AGenieCharacter) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<AGenieCharacter*>(this); }


#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGenieCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGenieCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGenieCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGenieCharacter); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AGenieCharacter(const AGenieCharacter& InCopy); \
public:


#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AGenieCharacter(const AGenieCharacter& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGenieCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGenieCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGenieCharacter)


#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_8_PROLOG
#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_RPC_WRAPPERS \
	unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_INCLASS \
	unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_POP


#define unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_INCLASS_NO_PURE_DECLS \
	unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_POP


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID unrealEngineProject_Source_unrealEngineProject_GenieCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS