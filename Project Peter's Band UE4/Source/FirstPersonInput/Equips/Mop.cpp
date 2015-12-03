// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Enemies/EnemyInteractable.h"
#include "Mop.h"

AMop::AMop()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootCollider"));

	MopHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("MopHitbox"));
	MopHitbox->AttachTo(RootComponent);
	MopHitbox->SetRelativeLocation(FVector(100, 0, -100));

	TempMopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TEMPMopModel"));
	TempMopMesh->AttachTo(RootComponent);
	TempMopMesh->SetRelativeLocation(FVector(100, 0, 0));

	OnActorBeginOverlap.AddDynamic(this, &AMop::OnActorOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMop::OnActorOverlapEnd);
}
void AMop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//Drawing the mop hitbox
	DrawDebugSphere(GetWorld(), MopHitbox->GetComponentLocation(), MopHitbox->GetScaledSphereRadius(), 32, FColor::Blue, true, DeltaTime*2);
	/*
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
	*/

	//GEngine->AddOnScreenDebugMessage(4, 2.f, FColor::Red, (TEXT("ForwardVector: " + RootComponent->GetForwardVector().ToString())));
	//GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Magenta, (TEXT("Rot: " + RootComponent->GetComponentRotation().ToString() )));

}

void AMop::OnActorOverlapBegin(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//Create an array to hold all of the overlapping actors on the player
		TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors, AEnemyInteractable::StaticClass());

		//Run enemyinteraction on every enemy the mop is colliding with.
		for (int i = 0; i < OverlappingActors.Num(); i++)
		{
			Cast<AEnemyInteractable>(OverlappingActors[i])->EnemyInteract(this);
		}
	}
}

void AMop::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner() && OtherActor->IsA(AEnemyInteractable::StaticClass()))
	{
		Cast<AEnemyInteractable>(OtherActor)->EnemyInteract(this);
	}
}