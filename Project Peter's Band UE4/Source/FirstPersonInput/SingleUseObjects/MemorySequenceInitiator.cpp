// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "MemorySequenceInitiator.h"


// Sets default values
AMemorySequenceInitiator::AMemorySequenceInitiator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetSphereRadius(50.f);
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AMemorySequenceInitiator::OnActorOverlapBegin);
}

// Called when the game starts or when spawned
void AMemorySequenceInitiator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMemorySequenceInitiator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMemorySequenceInitiator::OnActorOverlapBegin(AActor *OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (Cast<APlayerCharacter>(OtherActor) != nullptr)
		{
			bool Choice = Cast<APlayerCharacter>(OtherActor)->GetLastChoice();

			if (Choice == true)
			{
				//Teleport to MemSegA
				GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, TEXT("MEMORY SEGMENT A"));
				UGameplayStatics::OpenLevel(GetWorld(), MemorySegmentA);

				
			}
			else
			{
				//Teleport to MemSegB
				GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, TEXT("MEMORY SEGMENT B"));
				UGameplayStatics::OpenLevel(GetWorld(), MemorySegmentB);
			}
		}
	}
}

