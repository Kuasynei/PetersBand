// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MemorySequenceInitiator.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AMemorySequenceInitiator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMemorySequenceInitiator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	FName MemorySegmentA;

	UPROPERTY(EditAnywhere)
	FName MemorySegmentB;

protected:

	UFUNCTION()
	virtual void OnActorOverlapBegin(AActor *OtherActor);
};
