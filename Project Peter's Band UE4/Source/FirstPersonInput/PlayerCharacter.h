// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void SetWithin(bool wBool);

protected:

	bool isWithinTrigger;

	void ActivateButton();

	UPROPERTY(EditAnywhere)
	USceneComponent* Hand;


	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);

	UFUNCTION()
	virtual void OnActorOverlapEnd(AActor* OtherActor);



	
	
};
