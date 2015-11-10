// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BaseEquips.h"


// Sets default values
ABaseEquips::ABaseEquips()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEquips::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEquips::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}