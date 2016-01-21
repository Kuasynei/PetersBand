// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "InteractDoors.h"


// Sets default values
AInteractDoors::AInteractDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	DoorHinge = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Hinge"));
	DoorHinge->SetBoxExtent(FVector(5, 10, 5));
	DoorHinge->AddLocalOffset(FVector(-50, 0, 0));

	Collider->AttachTo(DoorHinge);

	RootComponent = DoorHinge;

}

// Called when the game starts or when spawned
void AInteractDoors::BeginPlay()
{
	Super::BeginPlay();

	bIsOpen = false;
	
}

// Called every frame
void AInteractDoors::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractDoors::Interact(AActor* Interactor)
{
		if (!bIsLocked)
		{
			FRotator CurrentRotation = AInteractDoors::GetActorRotation();
			if (bIsOpen)
			{
				CurrentRotation.Yaw -= 90;
				bIsOpen = false;
			}
			else
			{
				CurrentRotation.Yaw += 90;
				bIsOpen = true;
			}
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundEffect, GetActorLocation());

			SetActorRotation(CurrentRotation);
		}
}

