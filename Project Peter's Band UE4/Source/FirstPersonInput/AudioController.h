// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AudioController.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AAudioController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	TArray<USoundCue*> AudioFiles;

public:

	float GetCurrentSoundLength();

	int32 GetCount();

	USoundCue* GetSoundToPlay();
	
	void AddToCount();

private:

	int32 NumberOfLightsPassed;

	int32 ArraySize;



	
	
};
