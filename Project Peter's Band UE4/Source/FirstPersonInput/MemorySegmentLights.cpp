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
	SpotLight->Intensity = 5000.f;
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

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 740));

	
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

	if (VoiceOverTimer <= 0)
	{
		//
	}

}

void AMemorySegmentLights::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{

	}
}

void AMemorySegmentLights::CountDownTimer()
{
	--VoiceOverTimer;

	if (VoiceOverTimer <= 0)
	{
		// try and fire a projectile
		if (MemorySegmentLight != NULL)
		{
			UWorld* const World = GetWorld();
			FVector SpawnLocation = World->GetFirstPlayerController()->GetActorForwardVector() * 2000.f + FVector(0, 0, 740);

			if (World != NULL)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<AMemorySegmentLights>(MemorySegmentLight, SpawnLocation, GetActorRotation()); 
			}
		}
		//Destroy the light and sounds at the end of the voice over
		Destroy();

		GetWorldTimerManager().ClearTimer(VoiceOverTimerHandle);
	}
}

