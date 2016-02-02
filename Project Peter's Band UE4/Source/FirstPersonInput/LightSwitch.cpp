// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "LightSwitch.h"


// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight->Intensity = 3000.f;
	PointLight->bVisible = true;
	RootComponent = PointLight;

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
	PointLight->ToggleVisibility();
}