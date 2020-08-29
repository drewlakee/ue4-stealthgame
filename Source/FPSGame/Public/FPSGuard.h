// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "FPSGuard.generated.h"

UCLASS()
class FPSGAME_API AFPSGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSGuard();

protected:

	FRotator OriginalRotation;

	FTimerHandle TimerHandleResetRotation;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
	
	UFUNCTION()
    void OnPawnHeard(APawn* InstigatorPawn, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetRotation();

	void LookAtInstigatorDirection(const FVector& Location);

	void ResetLookDirectionAtOriginalAfterTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
