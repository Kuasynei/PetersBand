// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseEquips.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ABaseEquips : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquips();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	//An array pointer to this class, not to an instanced object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray< TSubclassOf<ABaseEquips> > Equips;

};
