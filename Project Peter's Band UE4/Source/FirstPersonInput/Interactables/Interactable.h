// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS(ABSTRACT)
class FIRSTPERSONINPUT_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//A virtual function that needs to be created for an interactable object to be used.
	UFUNCTION()
	virtual void Interact(AActor* Interactor) PURE_VIRTUAL(AInteractable::Interact, );

	//Checks if you can interact with the object
	bool IsInteractable;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Collider;
	
};
