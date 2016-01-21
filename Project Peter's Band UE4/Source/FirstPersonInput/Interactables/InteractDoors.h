// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractDoors.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AInteractDoors : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractDoors();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	virtual void Interact(AActor* Interactor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundCue* SoundEffect;

	UPROPERTY(EditAnywhere)
	UBoxComponent* DoorHinge;

	UPROPERTY(EditAnywhere)
	bool bIsLocked;

private:

	UPROPERTY(VisibleAnywhere)
	bool bIsOpen;

};
