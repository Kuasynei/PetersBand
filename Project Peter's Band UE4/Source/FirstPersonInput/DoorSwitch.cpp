// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "DoorSwitch.h"


// Sets default values
ADoorSwitch::ADoorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;

	Collider->SetBoxExtent(FVector(50, 50, 50));

	OnActorBeginOverlap.AddDynamic(this, &ADoorSwitch::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &ADoorSwitch::OnActorOverlapEnd);

	activated = false;
}

// Called when the game starts or when spawned
void ADoorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADoorSwitch::ActivateDoor()
{
	if (!activated)
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TEXT("Door Open"));
	else
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TEXT("Door Close"));
}

void ADoorSwitch::OnActorOverlap(AActor *OtherActor)
{
}

void ADoorSwitch::OnActorOverlapEnd(AActor *OtherActor)
{
}