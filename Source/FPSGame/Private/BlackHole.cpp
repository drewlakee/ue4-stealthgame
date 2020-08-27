// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KernelSphereComponent = CreateDefaultSubobject<USphereComponent>(FName("KernelSphereComponent"));
	KernelSphereComponent->SetSphereRadius(100);
	AttachSphereComponent = CreateDefaultSubobject<USphereComponent>(FName("AttachSphereComponent"));
	AttachSphereComponent->SetSphereRadius(3000);
	KernelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("KernelMeshComponent"));
	KernelMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	KernelSphereComponent->SetupAttachment(KernelMeshComponent);
	AttachSphereComponent->SetupAttachment(KernelMeshComponent);

	KernelSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::DestroyOverlappedActor);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackHole::DestroyOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappedComponents;
	AttachSphereComponent->GetOverlappingComponents(OverlappedComponents);

	for (UPrimitiveComponent* Component : OverlappedComponents)
	{
		if (Component && Component->IsSimulatingPhysics())
		{
			const float SphereRadius = AttachSphereComponent->GetScaledSphereRadius();
			const float ForceStrength = -2000;
			
			Component->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);	
		}
	}
}

