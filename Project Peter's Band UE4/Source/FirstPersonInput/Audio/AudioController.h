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

	//Array that holds all the audio files for the voice over.
	UPROPERTY(EditAnywhere)
	TArray<USoundCue*> AudioFiles;

public:

	//A function that returns the length of the sound that is playing
	float GetCurrentSoundLength();

	//Returns the amount of sounds that have been played
	int32 GetCount();

	//Returns that sound that needs to play next
	USoundCue* GetSoundToPlay();
	
	//Adds one to the count of sounds that have played
	void AddToCount();

	//Returns the size of the array of sounds (Useful for other docs that need to read this value)
	int32 GetArraySize();
private:

	//Holds the number of lights that have been spawned/moved
	int32 NumberOfLightsPassed;

	//The number of audio files in this holder
	int32 ArraySize;



	
	
};
