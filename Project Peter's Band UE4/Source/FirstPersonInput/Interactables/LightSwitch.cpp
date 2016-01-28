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

	if (!isOn)
	{
		SpotLight->ToggleVisibility();
		LightCollider->ToggleVisibility();
	}
}

// Called every frame
void ALightSwitch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	CheckOverlapping();
	if (isOn)
	{
		for (int i = 0; i < turtles.Num(); i++)
		{
			if (turtles[i] != nullptr)
			{
				turtles[i]->PowerOff();
			}
		}
	}
	else
	{
		for (int i = 0; i < turtles.Num(); i++)
		{
			turtles[i]->PowerOn();
			turtles.RemoveAt(i);
		}
	}
}

void ALightSwitch::Interact(AActor* Interactor)
{
	SpotLight->ToggleVisibility();
	LightCollider->ToggleVisibility();
	

	//SetActorEnableCollision(!isOn);
	isOn = !isOn;

}


void ALightSwitch::CheckOverlapping()
{

	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, ATurtle::StaticClass());

	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		if (OverlappingActors[i]->GetName().Contains("Turtle"))
		{
			//turtle = Cast<ATurtle>(OverlappingActors[i]);
			turtles.Add(Cast<ATurtle>(OverlappingActors[i]));
		}

	}

	//***SINGLE TURTLE USE***//

	//if (turtle != nullptr)
	//{
	//	if (isOn)
	//	{
	//		turtle->PowerOff();
	//	}
	//	else
	//	{
	//		turtle->PowerOn();
	//		turtle = nullptr;
	//	}
	//}
}

bool ALightSwitch::GetIsOn()
{
	return isOn;
}