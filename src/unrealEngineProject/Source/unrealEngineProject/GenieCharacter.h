// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GenieCharacter.generated.h"

// Create Enum Class
UENUM(BlueprintType)
enum class EHappyEnum : uint8
{
	Happy
};

UCLASS()
class UNREALENGINEPROJECT_API AGenieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGenieCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Create SpringArm Component
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	// Create Camera Component
	//UPROPERTY(EditAnywhere)
		//UCameraComponent* OurCamera;

	// Create HappyMovement Variable
	UPROPERTY(BlueprintReadWrite, Category = Components)
		bool HappyMovement;

	// Create IsHappy Function
	UFUNCTION(BlueprintCallable, Category = Functions, Meta = (ExpandEnumAsExecs = "Branches"))
		void IsHappy(EHappyEnum& Branches);
	
};
