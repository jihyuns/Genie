// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "GenieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINEPROJECT_API UGenieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	// Create GenieIsHappy variable
	UPROPERTY(BlueprintReadWrite, Category = Components)
		bool GenieIsHappy;
	
	
};
