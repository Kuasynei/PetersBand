// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "MemorySegmentLights.h"


// Sets default values
AMemorySegmentLights::AMemorySegmentLights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SpotLight;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->Intensity = 3000.f;
	SpotLight->SetIndirectLightingIntensity(0.0f);

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->AttachTo(RootComponent);

	OnActorEndOverlap.AddDynamic(this, &AMemorySegmentLights::OnActorOverlapEnd);

}

// Called when the game starts or when spawned
void AMemorySegmentLights::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), StartSound, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), VoiceOver, GetActorLocation());

}

// Called every frame
void AMemorySegmentLights::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMemorySegmentLights::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (VoiceOverTimer <= 0)
		{
			// try and fire a projectile
			if (MemorySegmentLight != NULL)
			{
				const FVector SpawnLocation = GetActorLocation() + FVector(20, 0, 0);

				UWorld* const World = GetWorld();
				if (World != NULL)
				{
					// spawn the projectile at the muzzle
					World->SpawnActor<AMemorySegmentLights>(MemorySegmentLight, SpawnLocation, GetActorRotation());
				}
			}
			//Destroy the light and sounds at the end of the voice over
			Destroy();
		}
		count++;
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT(" %i"), count));

	}
}


