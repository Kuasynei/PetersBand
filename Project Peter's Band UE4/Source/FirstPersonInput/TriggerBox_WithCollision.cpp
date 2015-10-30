// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "TriggerBox_WithCollision.h"


// Sets default values
ATriggerBox_WithCollision::ATriggerBox_WithCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;

	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox_WithCollision::OnActorOverlap);


}

// Called when the game starts or when spawned
void ATriggerBox_WithCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerBox_WithCollision::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATriggerBox_WithCollision::OnActorOverlap(AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Anything"));
	
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("SomethingInsideBox"));

		if (OtherActor->ActorHasTag(FName(TEXT("Player"))) == true)
		{
			
		}
	}
}

bool ATriggerBox_WithCollision::isLiftable()
{
	return canBeLifted;
}

void ATriggerBox_WithCollision::OnPickedUp()
{
	Collider->SetSimulatePhysics(false);
}

void ATriggerBox_WithCollision::OnDropped()
{
	Collider->SetSimulatePhysics(true);
}

void ATriggerBox_WithCollision::OpenDoor()
{
	if (!isDoor)
		return;
	else
	{
		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw += 90;
		SetActorRotation(CurrentRotation);
	}
}