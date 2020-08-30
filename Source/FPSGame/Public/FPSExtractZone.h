// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractZone.generated.h"

UCLASS()
class FPSGAME_API AFPSExtractZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractZone();
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* OverlapComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UDecalComponent* DecalComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ExtractZoneWrongSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float ExtractZoneWrongVolume = 1.f;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
