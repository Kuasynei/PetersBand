// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "WeightedSwitch.h"


// Sets default values
AWeightedSwitch::AWeightedSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;

	Collider->SetBoxExtent(FVector(50, 50, 10));

	OnActorBeginOverlap.AddDynamic(this, &AWeightedSwitch::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &AWeightedSwitch::OnActorOverlapEnd);

	Activated = false;
}

// Called when the game starts or when spawned
void AWeightedSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeightedSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeightedSwitch::OnActorOverlap(AActor *OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (ToActivate->ActorHasTag("Door"))
		{
			//Open Door
		}
		if (ToActivate->ActorHasTag("Light"))
		{
			//Turn On/Off Light
		}
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TEXT("Switch On"));
		//Activated = true;
	}
}

void AWeightedSwitch::OnActorOverlapEnd(AActor *OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TEXT("Switch Off"));
		//Activated = false;
	}
}
