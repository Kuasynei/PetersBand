// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NarrativeCollider.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ANarrativeCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANarrativeCollider();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USoundCue* NarrativeSound;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

protected:

	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);
		
	
};
