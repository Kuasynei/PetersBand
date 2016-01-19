// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnchovieCharacter.h"
#include "AnchovieController.h"
#include "Interactables/Interactable.h"
#include "Interactables/Lever.h"
#include "GameFramework/Actor.h"


// Sets default values
AAnchovieCharacter::AAnchovieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAnchovieController::StaticClass();


	skeleMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh1"));
	skeleMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh2"));
	skeleMesh3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh3"));
	skeleMesh4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh4"));
	skeleMesh5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh5"));
	skeleMesh6 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh6"));

	skeleMesh1->AttachTo(RootComponent);
	skeleMesh2->AttachTo(RootComponent);
	skeleMesh3->AttachTo(RootComponent);
	skeleMesh4->AttachTo(RootComponent);
	skeleMesh5->AttachTo(RootComponent);
	skeleMesh6->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AAnchovieCharacter::OnActorOverlaping);
}


void AAnchovieCharacter::OnActorOverlaping(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		LeverToCollideWith = Cast<ALever>(OtherActor);

		if (LeverToCollideWith != NULL)
		{
			if (LeverToCollideWith->GetIsActivated() == false)
			{
				LeverToCollideWith->Interact(this);
			}
		}

	}
}