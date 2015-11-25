// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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

	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	USoundCue* VoiceOver;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	USoundCue* StartSound;

	FTimerHandle VoiceOverTimerHandle;

protected:

	UFUNCTION()
	virtual void OnActorOverlapEnd(AActor* OtherActor);

	void CountDownTimer();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 VoiceOverTimer;

	int32 count;

	UPROPERTY(EditAnywhere, Category = MemoryLights)
	TSubclassOf<class AMemorySegmentLights> MemorySegmentLight;


};
