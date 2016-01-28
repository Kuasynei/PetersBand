// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interactables/Interactable.h"
#include "Interactables/LightSwitch.h"
#include "Interactables/Lever.h"
#include "AnchovieCharacter.generated.h"


UCLASS()
class FIRSTPERSONINPUT_API AAnchovieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnchovieCharacter();

	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh1;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh2;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh3;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh4;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh5;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleMesh6;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> Waypoints;

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

	UPROPERTY()
		ALightSwitch *TheSwitch;
};
