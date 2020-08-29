// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGuard.h"

#include "DrawDebugHelpers.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AFPSGuard::AFPSGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnPerceptionComponent"));
	
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSGuard::OnPawnHeard);
}

// Called when the game starts or when spawned
void AFPSGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSGuard::OnPawnSeen(APawn* Pawn)
{
	if (!Pawn) return;
	
	DrawDebugSphere(GetWorld(), Pawn->GetActorLocation(), 100.f, 12, FColor::Red, false, 1.0f);
}

void AFPSGuard::OnPawnHeard(APawn* InstigatorPawn, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 100.f, 12, FColor::Yellow, false, 1.0f);
}

