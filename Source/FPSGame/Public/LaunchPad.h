// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

private:
	
	void PlayActionsAtJump() const;

protected:

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* PadVolumeComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PadMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* PadDecalComponent;

	UPROPERTY(EditInstanceOnly, Category = "Launch")
	float LaunchAngle = 70.f;

	UPROPERTY(EditInstanceOnly, Category = "Launch")
	float LaunchStrength = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LaunchPadJumpSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float LaunchPadJumpSoundVolume = 1.f;

	UFUNCTION()
	void Launch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
