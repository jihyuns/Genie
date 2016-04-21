// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LoadingFile.generated.h"

UCLASS()
class UNREALENGINEPROJECT_API ALoadingFile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoadingFile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float RunningTime;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* LoadingText;

	void LoadingDisplay();
	void LoadingTimer();
	void LoadingFinished();

	FTimerHandle LoadingHandle;
	
};
