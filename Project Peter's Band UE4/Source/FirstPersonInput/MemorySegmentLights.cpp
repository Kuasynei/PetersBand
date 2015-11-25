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
	Collider->AttachTo(SpotLight);

	OnActorEndOverlap.AddDynamic(this, &AMemorySegmentLights::OnActorOverlapEnd);

}

// Called when the game starts or when spawned
void AMemorySegmentLights::BeginPlay()
{
	Super::BeginPlay();

	//Uncomment when a voice file is added to the light otherwise breaks ahoy.
	//VoiceOverTimer = VoiceOver->GetDuration();

	//Temp setting for testing
	VoiceOverTimer = 5;

	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), StartSound, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), VoiceOver, GetActorLocation());

	//Function that handles ticking down as the voice over is playing. This makes the voice over "Unskippable"
	//Takes in the Time handler, the object, a function that in this case lowers the Voice over timer value, counts down by one second and tells it to keep repeating until 0
	GetWorldTimerManager().SetTimer(VoiceOverTimerHandle, this, &AMemorySegmentLights::CountDownTimer, 1.0f, true);

}

// Called every frame
void AMemorySegmentLights::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Blue, FString::Printf(TEXT("Time Left on Voice Over %i"), VoiceOverTimer));

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
				const FVector SpawnLocation = OtherActor->GetActorForwardVector() * 2000.f + FVector(0, 0, 740);

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

void AMemorySegmentLights::CountDownTimer()
{
	--VoiceOverTimer;

	if (VoiceOverTimer <= 0)
	{
		GetWorldTimerManager().ClearTimer(VoiceOverTimerHandle);
	}
}

