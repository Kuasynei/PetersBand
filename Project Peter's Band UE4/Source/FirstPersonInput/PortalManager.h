// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PortalManager.generated.h"

USTRUCT()
struct FMapInstance
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* APortal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* BPortal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> MapElements;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* ActiveMapZone;

	FMapInstance()
	{
		ActiveMapZone = NULL;
	}
};

UCLASS()
class FIRSTPERSONINPUT_API APortalManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APortalManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> APortals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> BPortals;

	/*Lets the PortalManager know which map the player
	is in, after the PortalManager creates multiple map instances.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* OriginActiveMapZone;

	//A array of FMapInstance, each with a reference to all objects in the original map, and a respective ActiveMapZone.
	TArray<FMapInstance> MapInstances;

	//Hits zero every 0.25 seconds;
	float QuarterSeconds = 0;
};