// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Anchovies.h"


// Sets default values
AAnchovies::AAnchovies()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
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
}

// Called when the game starts or when spawned
void AAnchovies::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAnchovies::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

