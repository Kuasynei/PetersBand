// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "InteractDoors.h"


// Sets default values
AInteractDoors::AInteractDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetBoxExtent(FVector(50, 50, 10));

	SoundEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorOpeningSound"));
	static ConstructorHelpers::FObjectFinder<USoundCue> Sound(TEXT("SoundCue'/Game/Sounds/RAW_Door_Opening_2_Cue.RAW_Door_Opening_2_Cue'"));
	if (Sound.Object != NULL)
	{
		SoundEffect->SetSound(Sound.Object);
		SoundEffect->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void AInteractDoors::BeginPlay()
{
	Super::BeginPlay();

	active = true;
	
}

// Called every frame
void AInteractDoors::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractDoors::Interact(AActor* Interactor)
{
	if (active)
		active = false;
	else
		active = true;

	SoundEffect->SetWorldLocation(GetActorLocation());
	SoundEffect->Play();

	SetActorHiddenInGame(!active);
	SetActorEnableCollision(active);
	SetActorTickEnabled(active);
	//FRotator CurrentRotation = GetActorRotaion();
	//CurrentRotation.Yaw += 90;
	//SetActorRotation(CurrentRotation);
}

