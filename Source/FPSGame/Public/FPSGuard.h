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
	
	FRotator OriginalRotation;

	FTimerHandle TimerHandleResetRotation;

	EAIGuardState GuardState;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	
	UFUNCTION()
    void OnPawnHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetGuardState();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnGuardStateChange(EAIGuardState NewState);

	void SetFailedMission(APawn* Pawn);

	void LookAtInstigatorDirection(const FVector& Location);

	void ResetGuardStateAtOriginalAfterTimer();

	void SetGuardState(EAIGuardState NewState);

	void UpdatePatrollingState(bool bIsPatrollingToSet);
};
