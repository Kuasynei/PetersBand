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
		else if (Actor->ActorHasTag("Dynamic"))
		{
			OriginMap.DynamicElements.Add(Actor);
		}
	}
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

		//These are used to determine in what way to move the maps later on.
		OriginMap.LinkAPortal(&BPortalMap, "B");
		BPortalMap.LinkBPortal(&OriginMap, "A");

		OriginMap.LinkBPortal(&APortalMap, "A");
		APortalMap.LinkAPortal(&OriginMap,"B");

		//Spawning ActiveMapZones.
		SpawnInfo.Template = OriginMap.ActiveMapZone;
		APortalMap.ActiveMapZone = GetWorld()->SpawnActor(OriginMap.ActiveMapZone->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		APortalMap.ActiveMapZone->SetActorLabel(*(const FString("ActiveMapZone MAP " + FString::FromInt(i + 1) + "A")));
		BPortalMap.ActiveMapZone = GetWorld()->SpawnActor(OriginMap.ActiveMapZone->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
		BPortalMap.ActiveMapZone->SetActorLabel(*(const FString("ActiveMapZone MAP " + FString::FromInt(i + 1) + "B")));

		APortalMap.ActiveMapZone->SetActorLocation(APortalMap.ActiveMapZone->GetActorLocation() + MapAtoOrigin);
		BPortalMap.ActiveMapZone->SetActorLocation(BPortalMap.ActiveMapZone->GetActorLocation() + MapBtoOrigin);

		//Duplicating all dynamic elements for each map, based on the origin map.
		for (int j = 0; j < OriginMap.DynamicElements.Num(); j++)
		{
			SpawnInfo.Template = OriginMap.DynamicElements[j];

			AActor* ADynPortalActor = GetWorld()->SpawnActor(OriginMap.DynamicElements[j]->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
			APortalMap.DynamicElements.Add(ADynPortalActor);
			ADynPortalActor->SetActorLocation(ADynPortalActor->GetActorLocation() + MapAtoOrigin);

			AActor* BDynPortalActor = GetWorld()->SpawnActor(OriginMap.DynamicElements[j]->GetClass(), new FVector(0, 0, 0), new FRotator(0, 0, 0), SpawnInfo);
			BPortalMap.DynamicElements.Add(BDynPortalActor);
			BDynPortalActor->SetActorLocation(BDynPortalActor->GetActorLocation() + MapAtoOrigin);

		}

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

		//Finally adding the maps to MapInstances to be handled in tick.
		MapInstances.Add(APortalMap);
		MapInstances.Add(BPortalMap);
		MapInstances.Add(OriginMap);
	}
}

// Called every frame
void APortalManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//Runs every 0.25 seconds.
	QuarterSeconds += DeltaTime;
	if (QuarterSeconds > 0.25f)
	{
		//Check the ActiveMapZones of all MapInstances to determine which map the player is in.
		for (int i = 0; i < MapInstances.Num(); i++)
		{
			TArray<AActor*> OverlappingActors;
			MapInstances[i].ActiveMapZone->GetOverlappingActors(OverlappingActors);
			
			//If the player enters a new map....
			if (OverlappingActors.Num() != 0 && OverlappingActors.Contains(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
			{
				//Check if the new map has a portal that goes nowhere. 
				//If this map's APortal is missing a connecting map, hook it up.
				if (MapInstances[i].ALinkedTo == NULL)
				{
					//Find which map should be placed here.
					for (int j = 0; j < MapInstances.Num(); j++)
					{
						//We've found a map whose BPortal is not linked to anything.
						if (MapInstances[j].BLinkedTo == NULL)
						{
							//Move all elements in this unlinked map in such a way that the unlinked map hooks up with the new map.
							FVector BPortalToAPortal = FVector(MapInstances[i].APortal->GetActorLocation().X - MapInstances[j].BPortal->GetActorLocation().X,
															   MapInstances[i].APortal->GetActorLocation().Y - MapInstances[j].BPortal->GetActorLocation().Y,
															   MapInstances[i].APortal->GetActorLocation().Z - MapInstances[j].BPortal->GetActorLocation().Z);
							
							//Moving dynamic map elements.
							for (int k = 0; k < MapInstances[j].DynamicElements.Num(); k++)
							{
								MapInstances[j].DynamicElements[k]->SetActorLocation(MapInstances[j].DynamicElements[k]->GetActorLocation() + BPortalToAPortal);
							}

							//Moving generic map elements.
							for (int k = 0; k < MapInstances[j].MapElements.Num(); k++)
							{
								MapInstances[j].MapElements[k]->SetActorLocation(MapInstances[j].MapElements[k]->GetActorLocation() + BPortalToAPortal);
							}

							//Moving Portals
							MapInstances[j].APortal->SetActorLocation(MapInstances[j].APortal->GetActorLocation() + BPortalToAPortal);
							MapInstances[j].BPortal->SetActorLocation(MapInstances[j].BPortal->GetActorLocation() + BPortalToAPortal);

							//Moving ActiveMapZone
							MapInstances[j].ActiveMapZone->SetActorLocation(MapInstances[j].ActiveMapZone->GetActorLocation() + BPortalToAPortal);

							//Unlinking the OTHER MAP's BPortal just in case.
							FMapInstance* TertiaryMap;
							//OBTAIN REFERENCE TO MAP BEFORE UNLINKING
							TertiaryMap = MapInstances[j].UnlinkBPortal();
							if (TertiaryMap != NULL)
								TertiaryMap->UnlinkAPortal();

							//We're also unlinking its other portal since the whole map is moving.
							TertiaryMap = MapInstances[j].UnlinkAPortal();
							//OBTAIN REFERENCE TO MAP BEFORE UNLINKING
							if (TertiaryMap != NULL)
								TertiaryMap->UnlinkBPortal();

							//Linking the proper OTHER MAP portal with the NEW MAP.
							MapInstances[j].LinkBPortal(&MapInstances[i], "A");

							//Unlinking the NEW MAP's APortal so it can be hooked up by the OTHER MAP's BPortal.
							MapInstances[i].UnlinkAPortal();
							MapInstances[i].LinkAPortal(&MapInstances[j], "B");

							break;
						}
					}
				}
				//If this map's BPortal is missing a connecting map, hook it up.
				else if (MapInstances[i].BLinkedTo == NULL)
				{
					//Find which map should be placed here.
					for (int j = 0; j < MapInstances.Num(); j++)
					{
						//We've found a map whose BPortal is not linked to anything.
						if (MapInstances[j].ALinkedTo == NULL)
						{
							//Move all elements in this unlinked map in such a way that the unlinked map hooks up with the new map.
							FVector APortalToBPortal = FVector(MapInstances[i].BPortal->GetActorLocation().X - MapInstances[j].APortal->GetActorLocation().X,
								MapInstances[i].BPortal->GetActorLocation().Y - MapInstances[j].APortal->GetActorLocation().Y,
								MapInstances[i].BPortal->GetActorLocation().Z - MapInstances[j].APortal->GetActorLocation().Z);

							//Moving dynamic map elements.
							for (int k = 0; k < MapInstances[j].DynamicElements.Num(); k++)
							{
								MapInstances[j].DynamicElements[k]->SetActorLocation(MapInstances[j].DynamicElements[k]->GetActorLocation() + APortalToBPortal);
							}

							//Moving generic map elements.
							for (int k = 0; k < MapInstances[j].MapElements.Num(); k++)
							{
								MapInstances[j].MapElements[k]->SetActorLocation(MapInstances[j].MapElements[k]->GetActorLocation() + APortalToBPortal);
							}

							//Moving Portals
							MapInstances[j].APortal->SetActorLocation(MapInstances[j].APortal->GetActorLocation() + APortalToBPortal);
							MapInstances[j].BPortal->SetActorLocation(MapInstances[j].BPortal->GetActorLocation() + APortalToBPortal);

							//Moving ActiveMapZone
							MapInstances[j].ActiveMapZone->SetActorLocation(MapInstances[j].ActiveMapZone->GetActorLocation() + APortalToBPortal);

							//Unlinking the OTHER MAP's BPortal just in case.
							FMapInstance* TertiaryMap;
							TertiaryMap = MapInstances[j].UnlinkAPortal();
							if (TertiaryMap != NULL)
								TertiaryMap->UnlinkBPortal();

							//We're also unlinking its other portal since the whole map is moving.
							TertiaryMap = MapInstances[j].UnlinkBPortal();
							if (TertiaryMap != NULL)
								TertiaryMap->UnlinkAPortal();

							//Linking the proper OTHER MAP portal with the NEW MAP.
							MapInstances[j].LinkAPortal(&MapInstances[i], "B");

							//Unlinking the NEW MAP's BPortal so it can be hooked up with the OTHER MAP's APortal.
							TertiaryMap = MapInstances[i].UnlinkBPortal();
							MapInstances[i].LinkBPortal(&MapInstances[j], "A");

							break;
						}
					}
				}
				//Otherwise something went wrong.
				else
				{
					GEngine->AddOnScreenDebugMessage(200, 1.f, FColor::Green, MapInstances[i].ActiveMapZone->GetName() + "'s portals are already occupied.");
					break;
				}

				//Change the active map to the new map.
				ActiveMapIndex = i;
				GEngine->AddOnScreenDebugMessage(200, 1.f, FColor::Green, "Player found @: " + MapInstances[i].ActiveMapZone->GetName() +
					", @index: " + FString::FromInt(i));
				
				FString APortalDEBUG = "APortal: ";
				if (MapInstances[i].APortal != NULL)
				{
					APortalDEBUG += MapInstances[i].APortal->GetName();
				}

				if (MapInstances[i].ALinkedTo != NULL)
				{
					APortalDEBUG += "              ALinkedTo: " + MapInstances[i].ALinkedTo->GetName();
				}

				FString BPortalDEBUG = "BPortal: ";
				if (MapInstances[i].BPortal != NULL)
				{
					BPortalDEBUG += MapInstances[i].BPortal->GetName();
				}

				if (MapInstances[i].BLinkedTo != NULL)
				{
					BPortalDEBUG += "              BLinkedTo: " + MapInstances[i].BLinkedTo->GetName();
				}

				GEngine->AddOnScreenDebugMessage(300, 10.f, FColor::Red, APortalDEBUG);
				GEngine->AddOnScreenDebugMessage(400, 10.f, FColor::Red, BPortalDEBUG);
				break;

			}
		}

		QuarterSeconds = 0;
	}

	
}

