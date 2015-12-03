// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyInteractable.generated.h"

UCLASS(ABSTRACT)
class FIRSTPERSONINPUT_API AEnemyInteractable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	virtual void EnemyInteract(AActor* Interactor) PURE_VIRTUAL(AEnemyInteractable::EnemyInteract, );

	UFUNCTION()
	virtual void EnemyActivate(AActor* Interactor) PURE_VIRTUAL(AEnemyInteractable::EnemyActivate, );

protected:

	UPROPERTY(EditAnywhere)
	UShapeComponent* Collider;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	//Currently neeeded until skeleton is given for the turtle
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StatMesh;

	
	
};
