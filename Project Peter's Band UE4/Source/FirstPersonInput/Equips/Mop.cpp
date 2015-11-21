// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "EnemyInteractable.h"
#include "Mop.h"

AMop::AMop()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	MopHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MopHitbox"));
	MopHitbox->AttachTo(RootComponent);
	MopHitbox->SetRelativeLocation(FVector(100, 0, -100));

	OnActorBeginOverlap.AddDynamic(this, &AMop::OnActorOverlap);
}
void AMop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Drawing mop hitbox
	DrawDebugSphere(GetWorld(), MopHitbox->GetComponentLocation(), MopHitbox->GetUnscaledSphereRadius(), 64, FColor::Blue, true, DeltaTime * 2);

	//Debug drawn stick
	FVector StickTop = FVector(10, 20, 70);
	StickTop = RootComponent->GetComponentRotation().RotateVector(StickTop);
	StickTop += RootComponent->GetComponentTransform().GetLocation();

	FVector StickBottom = FVector(100, 0, -100);
	StickBottom = RootComponent->GetComponentRotation().RotateVector(StickBottom);
	StickBottom += RootComponent->GetComponentTransform().GetLocation();

	float StickRadius = 5.f;
	int32 CylinderSegments = 32;
	FColor StickColor = FColor::Red;

	DrawDebugCylinder(GetWorld(), StickTop, StickBottom, StickRadius, CylinderSegments, StickColor, true, DeltaTime * 2);

	//GEngine->AddOnScreenDebugMessage(4, 2.f, FColor::Red, (TEXT("ForwardVector: " + RootComponent->GetForwardVector().ToString())));
	//GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Magenta, (TEXT("Rot: " + RootComponent->GetComponentRotation().ToString() )));

}

void AMop::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//Create an array to hold all of the actors overlapping this mop.
		TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors, AEnemyInteractable::StaticClass());

		//Interact with every enemy being hit by the mop.
		for (int i = 0; i < OverlappingActors.Num(); i++)
		{
			AEnemyInteractable* CollidingShadowAnimal = Cast<AEnemyInteractable>(OverlappingActors[i]);
			CollidingShadowAnimal->EnemyInteract(this);
		}
	}
}

void AMop::OnActorEndOverlap(AActor* OtherActor)
{
	//Running the interact again on leave.
	Cast<AEnemyInteractable>(OtherActor)->EnemyInteract(this);
}