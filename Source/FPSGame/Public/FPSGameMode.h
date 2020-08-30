// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bIsGameOver;

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccess);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bIsMissionSuccess);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* MissionCompleteSuccessSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float MissionCompleteSuccessSoundVolume = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* MissionCompleteFailedSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	float MissionCompleteFailedSoundVolume = 1.f;
	
	void SetSpectatingViewPoint(APawn* InstigatorPawn);
};



