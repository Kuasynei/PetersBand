// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "NarrativeCollider.h"


// Sets default values
ANarrativeCollider::ANarrativeCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	OnActorBeginOverlap.AddDynamic(this, &ANarrativeCollider::OnActorOverlap);

}

// Called when the game starts or when spawned
void ANarrativeCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANarrativeCollider::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner() && OtherActor->GetName().Contains("Anna"))
	{
		if (NarrativeSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), NarrativeSound, GetActorLocation());
		}	
	}
}

