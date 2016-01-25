/* Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interactables/Interactable.h"
#include "Interactables/Lever.h"
#include "BossTurtleCharacter.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ABossTurtleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossTurtleCharacter();

	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> PathA;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> PathB;

	UPROPERTY(EditAnywhere)
		bool LightOn;

	UPROPERTY(EditAnywhere)
		float WaypointAt;

	UPROPERTY(EditAnywhere)
		FName DestinationKeyName;

	UFUNCTION()
		void NextWayPoint();

protected:


	UFUNCTION()
		void OnActorOverlaping(AActor* OtherActor);

	UPROPERTY()
		ALever *LeverToCollideWith;
};
*/