// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PadVolumeComponent = CreateDefaultSubobject<UBoxComponent>(FName("PadVolumeComponent"));
	PadMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("PadMeshComponent"));
	PadDecalComponent = CreateDefaultSubobject<UDecalComponent>(FName("PadDecalComponent"));
	SetRootComponent(PadVolumeComponent);
	PadMeshComponent->SetupAttachment(PadVolumeComponent);
	PadDecalComponent->SetupAttachment(PadMeshComponent);

	PadVolumeComponent->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::Launch);
}

void ALaunchPad::PlayActionsAtJump() const
{
	UGameplayStatics::PlaySoundAtLocation(this, LaunchPadJumpSound, GetActorLocation(), FMath::Clamp<float>(LaunchPadJumpSoundVolume, 0.f, 1.f));
}

void ALaunchPad::Launch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchAngle;
	const FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character)
	{
		Character->LaunchCharacter(LaunchVelocity, true, true);
		PlayActionsAtJump();
	}

	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		PlayActionsAtJump();
	} 
}

