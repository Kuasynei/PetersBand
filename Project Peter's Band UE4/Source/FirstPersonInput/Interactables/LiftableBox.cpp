// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "LiftableBox.h"


// Sets default values
ALiftableBox::ALiftableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	VisibleBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleBox"));
	VisibleBox->AttachTo(Collider);

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
	
	if (bIsAbove(Interactor))
	{
		Collider->SetSimulatePhysics(false);

		VisibleBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		this->AttachRootComponentTo(Cast<APlayerCharacter>(Interactor)->GetHand(), NAME_None, EAttachLocation::SnapToTarget);
		
		Player->SetObjectLifted(this);	
	}
}

void ALiftableBox::Drop(AActor* Player)
{
	Collider->SetSimulatePhysics(true);

	VisibleBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//THIS HAS TO BE THE PROBLEM
	RootComponent->DetachFromParent();

	RootComponent->SetWorldLocation(Cast<APlayerCharacter>(Player)->GetHand()->GetComponentLocation());
}

bool ALiftableBox::bIsAbove(AActor* Player)
{
	FVector PlayerToBox = Cast<APlayerCharacter>(Player)->GetActorLocation() - this->GetActorLocation();

	PlayerToBox.Normalize();

	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("Normalized Z Vector : %f"), PlayerToBox.Z));

	if (PlayerToBox.Z < 0.60f)
	{
		return true;
	}
	else
		return false;
}




