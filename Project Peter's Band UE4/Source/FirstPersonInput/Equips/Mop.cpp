// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Mop.h"

AMop::AMop()
{
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;
}

void AMop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Drawing a stick for the mop.
	FVector StickTop = FVector(50, 0, 140.f); //+ this->GetTransform().GetLocation();
	FVector StickBottom = FVector(50, 0, -140.f); //+ this->GetTransform().GetLocation();
	float StickRadius = 5.f;
	int32 CylinderSegments = 12;
	FColor StickColor = FColor::Red;

	DrawDebugCylinder(GetWorld(), StickTop, StickBottom, StickRadius, CylinderSegments, StickColor, true, 1);
}

void AMop::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		
	}
}