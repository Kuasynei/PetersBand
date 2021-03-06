// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Turtle.h"


// Sets default values
ATurtle::ATurtle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	//Uncomment when the skeletal is given to us instead of the Static Mesh
	//Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//Mesh->AttachTo(RootComponent);

	StatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatMesh"));
	StatMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurtle::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Bool: %s"), Collider->IsSimulatingPhysics() ? TEXT("true") : TEXT("false")));

}

void ATurtle::EnemyInteract(AActor* Interactor)
{
	Collider->SetSimulatePhysics(!Collider->IsSimulatingPhysics());
}


