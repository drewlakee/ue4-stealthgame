// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGuard.h"

#include "AIController.h"
#include "FPSGameMode.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AFPSGuard::AFPSGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnPerceptionComponent"));
	
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSGuard::OnPawnHeard);
}

TArray<AActor*> AFPSGuard::GetPatrolPoints() const
{
	return PatrolPoints;
}

// Called when the game starts or when spawned
void AFPSGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();

	SetGuardState(EAIGuardState::Idle);
}

void AFPSGuard::OnPawnSeen(APawn* Pawn)
{
	if (!Pawn) return;

	SetGuardState(EAIGuardState::Alerted);

	SetFailedMission(Pawn);
}

void AFPSGuard::SetFailedMission(APawn* Pawn)
{	
	AFPSGameMode* AfpsGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (AfpsGameMode && !AfpsGameMode->bIsGameOver)
	{
		AfpsGameMode->CompleteMission(Pawn, false); // mission failed by player, because guard inspect him
	}
}

void AFPSGuard::OnPawnHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (GuardState == EAIGuardState::Alerted) return; // alerted state have high priority
	
	LookAtInstigatorDirection(Location);

	SetGuardState(EAIGuardState::Suspicious);

	ResetGuardStateAtOriginalAfterTimer();
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

void AFPSGuard::ResetGuardStateAtOriginalAfterTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandleResetRotation);
	GetWorldTimerManager().SetTimer(TimerHandleResetRotation, this, &AFPSGuard::ResetGuardState, 3.0f, false);
}

void AFPSGuard::ResetGuardState()
{
	if (GuardState == EAIGuardState::Alerted) return; // alerted state have high priority

	SetActorRotation(OriginalRotation);
	
	SetGuardState(EAIGuardState::Idle);
}

void AFPSGuard::SetGuardState(EAIGuardState NewState)
{
	switch (NewState)
	{
		case EAIGuardState::Idle:
			UpdatePatrollingState(true);
			break;
		default:
			UpdatePatrollingState(false); // in other states patrolling is interrupted
	}

	GuardState = NewState;

	// look implementation at blueprint
	OnGuardStateChange(NewState);
}

void AFPSGuard::UpdatePatrollingState(bool bIsPatrollingToSet)
{
	bIsPatrolling = bIsPatrollingToSet;
	
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsBool(FName("IsPatrolling"), bIsPatrollingToSet);
		}
	}
}

