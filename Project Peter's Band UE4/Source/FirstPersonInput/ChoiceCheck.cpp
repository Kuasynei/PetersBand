// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "ChoiceCheck.h"


// Sets default values
AChoiceCheck::AChoiceCheck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	RootComponent = Collider;

	Collider->SetBoxExtent(FVector(300, 100, 200));

	OnActorBeginOverlap.AddDynamic(this, &AChoiceCheck::OnActorOverlap);
}

// Called when the game starts or when spawned
void AChoiceCheck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChoiceCheck::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AChoiceCheck::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (Cast<APlayerCharacter>(OtherActor)->GetLastChoice() == false)
		{
			Cast<APlayerCharacter>(OtherActor)->SetLastChoice(true);
		}
		else
		{
			Cast<APlayerCharacter>(OtherActor)->SetLastChoice(false);
		}
	}
}