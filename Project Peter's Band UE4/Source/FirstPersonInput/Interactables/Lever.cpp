// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Lever.h"


// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetBoxExtent(FVector(50, 50, 10));
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALever::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALever::Interact(AActor* OtherActor)
{
	if (bIsActivated)
	{
		bIsActivated = false;
	}
	else
	{
		bIsActivated = true;
	}

	for (int i = 0; i < TargetToAffect.Num(); i++)
	{
		TargetToAffect[i]->Interact(OtherActor);
	}
}

bool ALever::GetIsActivated()
{
	return bIsActivated;
}

