// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
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

	turtle = nullptr;
}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();

	isOn = true;
}

// Called every frame
void ALightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	CheckOverlapping();
}

void ALightSwitch::Interact(AActor* Interactor)
{
	SpotLight->ToggleVisibility();
	LightCollider->ToggleVisibility();
	

	SetActorEnableCollision(!isOn);
	isOn = !isOn;
}


void ALightSwitch::CheckOverlapping()
{

	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, ATurtle::StaticClass());

	//TArray<ATurtle*> turtles;

	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		if (OverlappingActors[i]->GetName().Contains("Turtle"))
		{
			turtle = Cast<ATurtle>(OverlappingActors[i]);
		}

		if (!turtle) continue;
	}

	if (turtle != nullptr)
	{
		if (isOn)
		{
			turtle->PowerOff();
		}
		else
		{
			turtle->PowerOn();
		}
	}
}