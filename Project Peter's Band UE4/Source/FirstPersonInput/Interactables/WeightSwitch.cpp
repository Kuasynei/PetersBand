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

	NumOfObjects = 0;

}

// Called when the game starts or when spawned
void AWeightSwitch::BeginPlay()
{
	Super::BeginPlay();

	bIsActivated = false;
	
}

// Called every frame
void AWeightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, AActor::StaticClass());

	for (int i = 0; i < TargetToAffect.Num(); i++)
	{
		if (TargetToAffect[i])
		{
			if (OverlappingActors.Num() >= 1)
			{
				if (!bIsActivated)
				{
					TargetToAffect[i]->Interact(Interactor);
					bIsActivated = true;
				}
			}
			else if (OverlappingActors.Num() == 0)
			{
				if (bIsActivated)
				{
					TargetToAffect[i]->Interact(Interactor);
					bIsActivated = false;
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Magenta, FString::Printf(TEXT("Objects Inside: %i"), OverlappingActors.Num()));
}

void AWeightSwitch::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		Interactor = OtherActor;
		NumOfObjects++;
	}
}

void AWeightSwitch::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, TEXT("OUT"));

		NumOfObjects--;
	}
}

