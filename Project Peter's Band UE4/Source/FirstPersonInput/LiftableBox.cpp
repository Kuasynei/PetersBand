// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "PlayerCharacter.h"
#include "LiftableBox.h"


// Sets default values
ALiftableBox::ALiftableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;
}

// Called when the game starts or when spawned
void ALiftableBox::BeginPlay()
{
	Super::BeginPlay();

	isLifted = false;
	
}

// Called every frame
void ALiftableBox::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALiftableBox::Interact(AActor* Interactor)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Active"));

	APlayerCharacter *Player = Cast<APlayerCharacter>(Interactor);

	//LIFT BOX CODE

	USceneComponent *PlayerHand = nullptr;

	PlayerHand = Player->GetHand();

	if (PlayerHand->AttachChildren.Num() > 0)
	{
		USceneComponent *AttachedObject;

		AttachedObject = PlayerHand->AttachChildren[0];

		Collider->SetSimulatePhysics(true);

		AttachedObject->DetachFromParent();
		
		AttachedObject->SetWorldLocation(PlayerHand->GetComponentLocation());
	}
	else
	{
		if (this->GetActorLocation().Z < Interactor->GetActorLocation().Z)
		{
			Collider->SetSimulatePhysics(false);
			this->AttachRootComponentTo(Cast<APlayerCharacter>(Interactor)->GetHand(), NAME_None, EAttachLocation::SnapToTarget);
		}
	}
}




