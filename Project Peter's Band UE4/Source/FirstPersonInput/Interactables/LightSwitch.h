// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Enemies/Turtle.h"
#include "LightSwitch.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ALightSwitch : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	virtual void Interact(AActor* Interactor);

	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* LightCollider;

	UPROPERTY(EditAnywhere)
	bool isOn;

	UFUNCTION()
	bool GetIsOn();

protected:


private:

	ATurtle *turtle;

	TArray<ATurtle*> turtles;

	void CheckOverlapping();
};
