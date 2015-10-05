// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BaseAI.h"
#include "SpawnerGamemode.h"

ASpawnerGamemode::ASpawnerGamemode(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	ConstructorHelpers::FObjectFinder<UBlueprint> AIBlueprint(TEXT("Blueprint'/Game/Blueprints/BaseAI_BP.BaseAI_BP'"));
	if (AIBlueprint.Object)
	{
		AIClass = (UClass*)AIBlueprint.Object->GeneratedClass;
	}
}

void ASpawnerGamemode::BeginPlay()
{
	FTimerHandle SomeVariable;
	GetWorldTimerManager().ClearTimer(SomeVariable);
	GetWorldTimerManager().SetTimer(SomeVariable, this, &ASpawnerGamemode::SpawnEntity, 2.f, true, -1.0f);
}

void ASpawnerGamemode::SpawnEntity()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		float xPos = FMath::FRandRange(0, 2000);
		float yPos = FMath::FRandRange(0, 2000);
		float zPos = 100.f;

		FVector const SpawnPosition(xPos, yPos, zPos);

		FActorSpawnParameters SpawnParms;
		SpawnParms.Owner = this;
		SpawnParms.Instigator = Instigator;


		ABaseAI* const SpawnedEntity = World->SpawnActor<ABaseAI>(AIClass, SpawnPosition, FRotator::ZeroRotator, SpawnParms);
		SpawnedEntity->SpawnDefaultController();
	}
}


