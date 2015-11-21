// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Mop.h"

AMop::AMop()
{
	RootCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RootCollider"));
	RootComponent = RootCollider;

	MopHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MopHitbox"));
	MopHitbox->AttachTo(RootComponent);
	MopHitbox->SetRelativeLocation(FVector(100, 0, -100));

	TempMopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TEMPMopModel"));
	TempMopMesh->AttachTo(RootComponent);
}
void AMop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Drawing a stick for the mop.
	FVector StickTop = FVector(10, 20, 70);
	StickTop = RootComponent->GetComponentRotation().RotateVector(StickTop);
	StickTop += RootComponent->GetComponentTransform().GetLocation();

	FVector StickBottom = FVector(100, 0, -100);
	StickBottom = RootComponent->GetComponentRotation().RotateVector(StickBottom);
	StickBottom += RootComponent->GetComponentTransform().GetLocation();

	float StickRadius = 5.f;
	int32 CylinderSegments = 32;
	FColor StickColor = FColor::Red;

	DrawDebugCylinder(GetWorld(), StickTop, StickBottom, StickRadius, CylinderSegments, StickColor, true, DeltaTime*2);

	//GEngine->AddOnScreenDebugMessage(4, 2.f, FColor::Red, (TEXT("ForwardVector: " + RootComponent->GetForwardVector().ToString())));
	//GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Magenta, (TEXT("Rot: " + RootComponent->GetComponentRotation().ToString() )));

}

void AMop::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		
	}
}