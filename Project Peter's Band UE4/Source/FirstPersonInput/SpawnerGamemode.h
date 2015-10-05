// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SpawnerGamemode.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API ASpawnerGamemode : public AGameMode
{
	GENERATED_BODY()
		
	ASpawnerGamemode(const class FObjectInitializer&);

	UPROPERTY(EditDefaultsOnly, Category = AIClass)
	TSubclassOf<ABaseAI> AIClass;
		

	virtual void BeginPlay();

protected:
	void SpawnEntity();
};
