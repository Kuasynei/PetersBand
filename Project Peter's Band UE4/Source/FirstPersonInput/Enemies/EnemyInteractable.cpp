// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "EnemyInteractable.h"


// Sets default values
AEnemyInteractable::AEnemyInteractable()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyInteractable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

