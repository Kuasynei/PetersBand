// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyInteractable.h"
#include "Turtle.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ATurtle : public AEnemyInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurtle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	virtual void EnemyInteract(AActor* Interactor);

	UFUNCTION()
		void PowerOff();
	UFUNCTION()
		void PowerOn();

protected:

private:

	bool bVisible;

};
