// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Turtle.h"


// Sets default values
ATurtle::ATurtle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StatMesh;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();

	bVisible = true;
	
}

// Called every frame
void ATurtle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Black, FString::Printf(TEXT("Turtle Physics: %s"), Collider->IsSimulatingPhysics() ? TEXT("true") : TEXT("false")));
}

void ATurtle::EnemyInteract(AActor* Interactor)
{
	//DO INTERACTIONS HERE
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, StatMesh->IsSimulatingPhysics() ? TEXT("false") : TEXT("true"));
	if (StatMesh->IsSimulatingPhysics())
	{
		StatMesh->SetSimulatePhysics(false);
	}
	else if (!StatMesh->IsSimulatingPhysics())
	{
		StatMesh->SetSimulatePhysics(true);
	}
}

void ATurtle::PowerOff()
{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
}

void ATurtle::PowerOn()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
