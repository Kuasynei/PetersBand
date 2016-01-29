// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PortalManager.generated.h"

USTRUCT()
struct FMapInstance
{
	GENERATED_USTRUCT_BODY()

	//Reference to this map's APortal, the portal that the APortal is linked to, whether or not it's linked, and the other portal's map.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* APortal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* ALinkedTo;

	FMapInstance* ALinkedMap;

	//Reference to this map's BPortal, the portal that the BPortal is linked to, and whether or not it's linked.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* BPortal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* BLinkedTo;

	FMapInstance* BLinkedMap;

	//Contains all movable elements that need to be sync'd between maps.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> DynamicElements;

	//All Duplicable actors that aren't DynamicElements.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> MapElements;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* ActiveMapZone;

	//Takes in a MapInstance. Enter "A" or "B" to specify which portal to use from that MapInstance. Defaults to "A".
	void LinkAPortal(FMapInstance* INOtherMap, FString Specification)
	{
		if (Specification == "B")
		{
			ALinkedTo = INOtherMap->BPortal;
			ALinkedMap = INOtherMap;
		}
		else
		{
			ALinkedTo = INOtherMap->APortal;
			ALinkedMap = INOtherMap;
		}
	}

	FMapInstance* UnlinkAPortal()
	{
		FMapInstance* HoldThisMapForMe = ALinkedMap;
		ALinkedMap = NULL;
		ALinkedTo = NULL;

		return HoldThisMapForMe;
	}

	//Takes in a MapInstance. Enter "A" or "B" to specify which portal to use from that MapInstance. Defaults to "A".
	void LinkBPortal(FMapInstance* INOtherMap, FString Specification)
	{
		if (Specification == "B")
		{
			BLinkedTo = INOtherMap->BPortal;
			BLinkedMap = INOtherMap;
		}
		else
		{
			BLinkedTo = INOtherMap->APortal;
			BLinkedMap = INOtherMap;
		}
	}

	FMapInstance* UnlinkBPortal()
	{
		FMapInstance* HoldThisMapForMe = BLinkedMap;
		BLinkedMap = NULL;
		BLinkedTo = NULL;

		return HoldThisMapForMe;
	}

	FMapInstance()
	{
		ALinkedMap = NULL;
		ALinkedTo = NULL;

		BLinkedMap = NULL;
		BLinkedTo = NULL;

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

	//For determining which map within MapInstances should be the map other maps revolve around.
	int ActiveMapIndex = 0;

	//Hits zero every 0.25 seconds;
	float QuarterSeconds = 0;
};