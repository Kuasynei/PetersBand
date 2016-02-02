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

	if (OriginActiveMapZone == NULL)
	{
		GEngine->AddOnScreenDebugMessage(200, -1, FColor::Red, "PortalManager requires an ActiveMapZone to function.");
		return;
	}

	//////////
	/*Defining the OriginMap for duplication. Obtaining a root component to
	establish */
	FMapInstance OriginMap;
	OriginMap.APortal = APortals[0];
	OriginMap.BPortal = BPortals[0];
	OriginMap.ActiveMapZone = OriginActiveMapZone;
	
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);
	for (AActor* Actor : AllActors)
	{
		if (Actor->ActorHasTag("Duplicable"))
		{
			OriginMap.MapElements.Add(Actor);
		}
	}

	MapInstances.Add(OriginMap);
	//////////


	//Creating additional maps, based on the OriginMap.
	for (int i = 0; i < APortals.Num(); i++)
	{
		FMapInstance APortalMap;
		FMapInstance BPortalMap;

		//Spawning PortalDoors for each map.
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Template = OriginMap.APortal;
		APortalMap.APortal = GetWorld()->SpawnActor(OriginMap.APortal->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		APortalMap.APortal->SetActorLabel(*(const FString("PortalA MAP " + FString::FromInt(i + 1) + "A")));

		SpawnInfo.Template = OriginMap.BPortal;
		APortalMap.BPortal = GetWorld()->SpawnActor(OriginMap.BPortal->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		APortalMap.BPortal->SetActorLabel(*(const FString("PortalB MAP " + FString::FromInt(i + 1) + "A")));

		SpawnInfo.Template = OriginMap.APortal;
		BPortalMap.APortal = GetWorld()->SpawnActor(OriginMap.APortal->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		BPortalMap.APortal->SetActorLabel(*(const FString("PortalA MAP " + FString::FromInt(i + 1) + "B")));

		SpawnInfo.Template = OriginMap.BPortal;
		BPortalMap.BPortal = GetWorld()->SpawnActor(OriginMap.BPortal->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		BPortalMap.BPortal->SetActorLabel(*(const FString("PortalB MAP " + FString::FromInt(i + 1) + "B")));

		//Moving the Portal Doors to align with the Origin Map, and saving the transform to be used for other map elements.
		FVector MapAtoOrigin = FVector(OriginMap.BPortal->GetActorLocation().X - APortalMap.APortal->GetActorLocation().X,
									   OriginMap.BPortal->GetActorLocation().Y - APortalMap.APortal->GetActorLocation().Y,
									   OriginMap.BPortal->GetActorLocation().Z - APortalMap.APortal->GetActorLocation().Z);
		FVector MapBtoOrigin = FVector(OriginMap.APortal->GetActorLocation().X - BPortalMap.BPortal->GetActorLocation().X,
									   OriginMap.APortal->GetActorLocation().Y - BPortalMap.BPortal->GetActorLocation().Y,
									   OriginMap.APortal->GetActorLocation().Z - BPortalMap.BPortal->GetActorLocation().Z);

		APortalMap.APortal->SetActorLocation(APortalMap.APortal->GetActorLocation() + MapAtoOrigin);
		APortalMap.BPortal->SetActorLocation(APortalMap.BPortal->GetActorLocation() + MapAtoOrigin);

		BPortalMap.APortal->SetActorLocation(BPortalMap.APortal->GetActorLocation() + MapBtoOrigin);
		BPortalMap.BPortal->SetActorLocation(BPortalMap.BPortal->GetActorLocation() + MapBtoOrigin);

		//Spawning ActiveMapZones.
		SpawnInfo.Template = OriginMap.ActiveMapZone;
		APortalMap.ActiveMapZone = GetWorld()->SpawnActor(OriginMap.ActiveMapZone->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		APortalMap.ActiveMapZone->SetActorLabel(*(const FString("ActiveMapZone MAP " + FString::FromInt(i + 1) + "A")));
		BPortalMap.ActiveMapZone = GetWorld()->SpawnActor(OriginMap.ActiveMapZone->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		BPortalMap.ActiveMapZone->SetActorLabel(*(const FString("ActiveMapZone MAP " + FString::FromInt(i + 1) + "B")));

		APortalMap.ActiveMapZone->SetActorLocation(APortalMap.ActiveMapZone->GetActorLocation() + MapAtoOrigin);
		BPortalMap.ActiveMapZone->SetActorLocation(BPortalMap.ActiveMapZone->GetActorLocation() + MapBtoOrigin);

		//Duplicating objects for each map. based on the origin map.
		for (int j = 0; j < OriginMap.MapElements.Num(); j++)
		{
			SpawnInfo.Template = OriginMap.MapElements[j];

			AActor* APortalActor = GetWorld()->SpawnActor(OriginMap.MapElements[j]->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
			APortalMap.MapElements.Add(APortalActor);
			APortalActor->SetActorLocation(APortalActor->GetActorLocation() + MapAtoOrigin);

			AActor* BPortalActor = GetWorld()->SpawnActor(OriginMap.MapElements[j]->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
			BPortalMap.MapElements.Add(BPortalActor);
			BPortalActor->SetActorLocation(BPortalActor->GetActorLocation() + MapBtoOrigin);
		}


	}
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

