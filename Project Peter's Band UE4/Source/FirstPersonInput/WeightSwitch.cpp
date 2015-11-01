// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "WeightSwitch.h"


// Sets default values
AWeightSwitch::AWeightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;

	OnActorBeginOverlap.AddDynamic(this, &AWeightSwitch::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &AWeightSwitch::OnActorOverlapEnd);

}

// Called when the game starts or when spawned
void AWeightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeightSwitch::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, TEXT("IN"));

		TargetToAffect->Interact(OtherActor);
	}
}

void AWeightSwitch::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, TEXT("OUT"));
	}
}

