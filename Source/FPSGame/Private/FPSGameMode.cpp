// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "SpectatingViewPoint.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
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

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr); // in anyway disabling controller under that pawn
	}

	SetSpectatingViewPoint(InstigatorPawn);

	// Look implementation at blueprint
	OnMissionCompleted(InstigatorPawn);
}
