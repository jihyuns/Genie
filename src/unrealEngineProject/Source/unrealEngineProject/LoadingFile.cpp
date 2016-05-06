// Fill out your copyright notice in the Description page of Project Settings.

#include "unrealEngineProject.h"
#include "LoadingFile.h"


// Sets default values
ALoadingFile::ALoadingFile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LoadingText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Genie"));
	LoadingText->SetHorizontalAlignment(EHTA_Center);
	LoadingText->SetWorldSize(200.0f);
	RootComponent = LoadingText;

}

// Called when the game starts or when spawned
void ALoadingFile::BeginPlay()
{
	Super::BeginPlay();
	
	LoadingDisplay();
	GetWorldTimerManager().SetTimer(LoadingHandle, this, &ALoadingFile::LoadingTimer, 1.0f, true);
}

// Called every frame
void ALoadingFile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void ALoadingFile::LoadingDisplay()
{
	LoadingText->SetText(TEXT("Genie"));
}

void ALoadingFile::LoadingTimer()
{
	LoadingDisplay();

	if (FPaths::FileExists("C:\\Users\\gclab\\Desktop\\data.txt"))
	{
		GetWorldTimerManager().ClearTimer(LoadingHandle);
		LoadingFinished();
	}
}

void ALoadingFile::LoadingFinished()
{
	UGameplayStatics::OpenLevel(GetWorld(), "GenieStart");
}

