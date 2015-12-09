// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AudioController.h"


// Sets default values
AAudioController::AAudioController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Starts the number of lights passed at 0
	NumberOfLightsPassed = 0;
}

// Called when the game starts or when spawned
void AAudioController::BeginPlay()
{
	Super::BeginPlay();

	//Sets the array size to the proper number
	ArraySize = AudioFiles.Num();
}

// Called every frame
void AAudioController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

float AAudioController::GetCurrentSoundLength()
{
	//If we still havent passed the max array size then return the length of the sounds that is currently playing
	if (NumberOfLightsPassed <= ArraySize)
	{
		if (AudioFiles[NumberOfLightsPassed - 1] != NULL)
			return AudioFiles[NumberOfLightsPassed - 1]->GetDuration();
		else
			return 2.f;
	}
	else
	{
		return 2.f;
	}
}

int32 AAudioController::GetCount()
{
	//Returns an int relating to the number of times the light has moved
	return NumberOfLightsPassed;
}

USoundCue* AAudioController::GetSoundToPlay()
{
	//As long as there is a sound to play then return a sound to play. Otherwise return NULL
	if (NumberOfLightsPassed <= ArraySize)
	{
		if (NumberOfLightsPassed > 0)
		{
			if (AudioFiles[NumberOfLightsPassed - 1] != NULL)
			{
				return AudioFiles[NumberOfLightsPassed - 1];
			}
			else
				return NULL;
		}
		else return NULL;
	}
	else
	{
		return NULL;
	}
}

void AAudioController::AddToCount()
{
	NumberOfLightsPassed++;
}

int32 AAudioController::GetArraySize()
{
	return ArraySize;
}

