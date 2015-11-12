// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Turtle.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ATurtle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurtle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	//Currently neeeded until skeleton is given for the turtle
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StatMesh;


	
	
};
