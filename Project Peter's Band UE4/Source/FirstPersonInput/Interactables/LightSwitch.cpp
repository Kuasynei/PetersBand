// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Enemies/Turtle.h"
#include "LightSwitch.h"


// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = SpotLight;
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("PointLight1"));
	SpotLight->Intensity = 3000.f;
	SpotLight->SetIndirectLightingIntensity(0.0f);
	SpotLight->bVisible = true;

	LightCollider = CreateDefaultSubobject<USphereComponent>(TEXT("LightCollider"));
	LightCollider->AttachTo(SpotLight);
	LightCollider->InitSphereRadius(600.f);
	LightCollider->RelativeLocation = FVector(600, 0, 0);

	OnActorBeginOverlap.AddDynamic(this, &ALightSwitch::OnActorOverlap);

}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALightSwitch::Interact(AActor* Interactor)
{
	SpotLight->ToggleVisibility();
	LightCollider->ToggleVisibility();
}

void ALightSwitch::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		ATurtle* EnemyInteractor = Cast<ATurtle>(OtherActor);
		EnemyInteractor->EnemyActivate(this);
	}
}