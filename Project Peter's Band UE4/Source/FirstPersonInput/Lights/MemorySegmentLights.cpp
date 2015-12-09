// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "MemorySegmentLights.h"


// Sets default values
AMemorySegmentLights::AMemorySegmentLights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SpotLight;

	//Creates a spotlight for us to place the model within
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->Intensity = 5000.f;
	SpotLight->SetIndirectLightingIntensity(0.0f);

	//Creates a collision box that will be used when skippng is implemented
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->AttachTo(SpotLight);

}

// Called when the game starts or when spawned
void AMemorySegmentLights::BeginPlay()
{
	Super::BeginPlay();

	StartTimer();

}

// Called every frame
void AMemorySegmentLights::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMemorySegmentLights::CountDownTimer()
{
	--VoiceOverTimer;

	if (VoiceOverTimer <= 0)
	{
		//When the timer is empty clear the timer so it doesnt count into the negatives, and then run the audio finished function
		GetWorldTimerManager().ClearTimer(VoiceOverTimerHandle);
		AudioFinished();
	}
}

void AMemorySegmentLights::StartTimer()
{
	//Gets the length of the audio cue that is about to start playing and sets the timer to that value. If the count is 0 (Meaning this is the first light) it will only show for 2 seconds.
	if (AudioController->GetCount() > 0)
	{
		VoiceOverTimer = AudioController->GetCurrentSoundLength();
	}
	else
	{
		VoiceOverTimer = 2.f;
	}

	//Function that handles ticking down as the voice over is playing. This makes the voice over "Unskippable"
	//Takes in the Time handler, the object, a function that in this case lowers the Voice over timer value, counts down by one second and tells it to keep repeating until 0
	GetWorldTimerManager().SetTimer(VoiceOverTimerHandle, this, &AMemorySegmentLights::CountDownTimer, 1.0f, true);

	//GameplayStatics function that plays a sound at the location of the light so we can properly use audio falloff.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), StartSound, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioController->GetSoundToPlay(), GetActorLocation());

}

void AMemorySegmentLights::AudioFinished()
{
	//As long as the memory segment light exists, move the light to 20m from the direction the character is facing. This relies of the forward vector the character being correct.
	if (MemorySegmentLight != NULL)
	{
		UWorld* const World = GetWorld();
		FVector moveLocation = World->GetFirstPlayerController()->GetActorForwardVector() * 2000.f;

		SetActorLocation(FVector(moveLocation.X, moveLocation.Y, 740));
	}

	//If there are no more audio files to play then teleport the player out of the map
	if (AudioController->GetCount() > AudioController->GetArraySize())
	{
		//Teleport the player out of the memory segment map
		UGameplayStatics::OpenLevel(GetWorld(), "SectionTwo");
	}

	//Tell the audio controller that we are ready for another sound
	AudioController->AddToCount();

	//Start the timer again
	StartTimer();
}

