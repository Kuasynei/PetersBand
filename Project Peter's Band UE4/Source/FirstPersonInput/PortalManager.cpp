// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "PortalManager.h"

// Sets default values
APortalManager::APortalManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortalManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (APortals.Num() != BPortals.Num())
	{
		GEngine->AddOnScreenDebugMessage(100, -1, FColor::Red, "PortalManager requires PortalA and PortalB to have an equal number of elements.");
		return;
	}

	MapInstance OriginMap;
	//OriginMap.MapElements
	
}

// Called every frame
void APortalManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TArray<AActor*> OverlappingActors;

	//Runs every 0.25 seconds.
	QuarterSeconds += DeltaTime;
	if (QuarterSeconds > 0.25f)
	{
		/*DETECTIONZONES
		ActiveMapZone->GetOverlappingActors(OverlappingActors);*/

		QuarterSeconds = 0;
	}


	/*DETECTIONZONES
	if (OverlappingActors.Num() != 0 && OverlappingActors.Contains(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		GEngine->AddOnScreenDebugMessage(200, 1.f, FColor::Green, "PlayerDetected");
	}
	*/
}

