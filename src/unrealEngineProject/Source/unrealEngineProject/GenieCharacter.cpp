// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealEngineProject.h"
#include "GenieCharacter.h"


// Sets default values
AGenieCharacter::AGenieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/***	Create Our Components	***/
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create SpringArm Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;

	// Create Camera Component
	//OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	//OurCamera->AttachTo(SpringArm);
	//OurCamera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AGenieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenieCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGenieCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

// Check Genie's Emotion is Happy
void AGenieCharacter::IsHappy(EHappyEnum& Branches)
{
	if (FPaths::FileExists("C:\\Users\\gclab\\Desktop\\happy.txt"))
	{
		Branches = EHappyEnum::Happy;
	}
}

