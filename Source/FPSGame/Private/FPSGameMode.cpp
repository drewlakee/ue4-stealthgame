// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	bIsGameOver = false;
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccess)
{
	if (bIsGameOver) return;
	
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr); // in anyway disabling controller under that pawn
	}

	SetSpectatingViewPoint(InstigatorPawn);

	if (bIsMissionSuccess)
	{
		UGameplayStatics::PlaySoundAtLocation(this, MissionCompleteSuccessSound, InstigatorPawn->GetActorLocation(),FMath::Clamp<float>(MissionCompleteSuccessSoundVolume, 0.f, 1.f));	
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, MissionCompleteFailedSound, InstigatorPawn->GetActorLocation(),FMath::Clamp<float>(MissionCompleteSuccessSoundVolume, 0.f, 1.f));	
	}

	bIsGameOver = true;
	
	// Look implementation at blueprint
	OnMissionCompleted(InstigatorPawn, bIsMissionSuccess);
}

void AFPSGameMode::SetSpectatingViewPoint(APawn* InstigatorPawn)
{
	APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
	
	AActor* SpectatingActor = UGameplayStatics::GetActorOfClass(this, SpectatingActorClass);
	
	if (SpectatingActor)
	{
		PlayerController->SetViewTargetWithBlend(SpectatingActor, 1.5f);	
	}
}