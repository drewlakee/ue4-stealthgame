// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGuard.h"
#include "FPSGameMode.h"
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

	OriginalRotation = GetActorRotation();
}

// Called every frame
void AFPSGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSGuard::SetFailedMission(APawn* Pawn)
{	
	AFPSGameMode* AfpsGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (AfpsGameMode && !AfpsGameMode->bIsGameOver)
	{
		AfpsGameMode->CompleteMission(Pawn, false); // mission failed by player, because guard inspect him
	}
}

void AFPSGuard::OnPawnSeen(APawn* Pawn)
{
	if (!Pawn) return;

	SetFailedMission(Pawn);
}

void AFPSGuard::OnPawnHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	LookAtInstigatorDirection(Location);

	ResetLookDirectionAtOriginalAfterTimer();
}

void AFPSGuard::LookAtInstigatorDirection(const FVector& Location)
{
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewLookDirection = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookDirection.Pitch = 0.0f;
	NewLookDirection.Roll = 0.0f;
	
	SetActorRotation(NewLookDirection);
}

void AFPSGuard::ResetLookDirectionAtOriginalAfterTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandleResetRotation);
	GetWorldTimerManager().SetTimer(TimerHandleResetRotation, this, &AFPSGuard::ResetRotation, 3.0f, false);
}

void AFPSGuard::ResetRotation()
{
	SetActorRotation(OriginalRotation);
}

