// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"

#include "FPSGameState.h"
#include "FPSHUD.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_FPSPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	bIsGameOver = false;

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccess)
{
	if (bIsGameOver) return;
	
	SetAllPlayersAtSpectatingViewPoint();

	bIsGameOver = true;
	
	AFPSGameState* GameState = GetGameState<AFPSGameState>();
	if (GameState)
	{
		GameState->MulticastOnMissionComplete(InstigatorPawn, bIsMissionSuccess);
	}
}

void AFPSGameMode::SetAllPlayersAtSpectatingViewPoint() const
{
	AActor* SpectatingActor = UGameplayStatics::GetActorOfClass(this, SpectatingActorClass);

	// if no spectating actor at level then we doesn't need to do next things
	if (!SpectatingActor) return;

	const int32 NumPlayerControllers = GetWorld()->GetNumPlayerControllers();

	for (int32 PlayerControllerIndex = 0; PlayerControllerIndex < NumPlayerControllers; PlayerControllerIndex++)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, PlayerControllerIndex);
		if (PlayerController)
		{
			PlayerController->SetViewTargetWithBlend(SpectatingActor, 1.5f);
		}
	}
	
}