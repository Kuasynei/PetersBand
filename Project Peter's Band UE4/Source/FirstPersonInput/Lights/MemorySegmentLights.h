// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Audio/AudioController.h"
#include "MemorySegmentLights.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AMemorySegmentLights : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMemorySegmentLights();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	//A spot light component that can shines light in a controlled cone
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotLight;

	//A collider that is used for skipping the audio, not needed in this build
	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	//The sound of the light turning on
	UPROPERTY(EditAnywhere, Category = Gameplay)
	USoundCue* StartSound;

	//A handler for the timer that is linked to the length of the sound
	FTimerHandle VoiceOverTimerHandle;

protected:

	//A function taht holds actions to take every time the timer ticks
	void CountDownTimer();

	//What to do when the audio finishes playing
	void AudioFinished();

	//What to do before and when the timer starts
	void StartTimer();
public:

	//An int to hold the length of the sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 VoiceOverTimer;

	//An instance of a light to spawn a new light, ditched in favor of just moving the light
	UPROPERTY(EditAnywhere, Category = MemoryLights)
	TSubclassOf<class AMemorySegmentLights> MemorySegmentLight;

	//A public reference to the audio controller object
	UPROPERTY(EditAnywhere)
	AAudioController* AudioController;
};
