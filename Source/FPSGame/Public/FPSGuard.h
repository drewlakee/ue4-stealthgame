// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSGuard.generated.h"

UENUM(BlueprintType)
enum class EAIGuardState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSGuard : public ACharacter
{
	GENERATED_BODY()

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	
	// Sets default values for this character's properties
	AFPSGuard();

	TArray<AActor*> GetPatrolPoints() const;

	UPROPERTY(EditInstanceOnly, Category = "Patrol Navigation")
	bool bIsPatrolling = true;

protected:

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditInstanceOnly, Category = "Patrol Navigation")
	TArray<AActor*> PatrolPoints;

	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIGuardState GuardState;
	
	FRotator OriginalRotation;

	FTimerHandle TimerHandleResetRotation;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	
	UFUNCTION()
    void OnPawnHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetGuardState();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnGuardStateChange(EAIGuardState NewState);

	UFUNCTION()
	void OnRep_GuardState();
	
	void SetFailedMission(APawn* Pawn);

	void LookAtInstigatorDirection(const FVector& Location);

	void ResetGuardStateAtOriginalAfterTimer();

	void SetGuardState(EAIGuardState NewState);

	void UpdatePatrollingState(bool bIsPatrollingToSet);
};
