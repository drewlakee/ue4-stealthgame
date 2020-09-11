// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"

#include "FPSCharacter.h"
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

	SetSpectatingViewPointForAllPlayer();

	bIsGameOver = true;
	
	AFPSGameState* GameState = GetGameState<AFPSGameState>();
	if (GameState)
	{
		GameState->MulticastOnMissionComplete(InstigatorPawn, bIsMissionSuccess);
	}
}

void AFPSGameMode::SetSpectatingViewPointForAllPlayer()
{
	TArray<AActor*> Players;
	
	UGameplayStatics::GetAllActorsOfClass(this, AFPSCharacter::StaticClass(), Players);
	
	AActor* SpectatingActor = UGameplayStatics::GetActorOfClass(this, SpectatingActorClass);
	
	if (SpectatingActor)
	{
		for (AActor* PlayerActor : Players)
		{
			AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(PlayerActor);
			if (PlayerCharacter)
			{
				PlayerCharacter->GetController()->CastToPlayerController()->SetViewTargetWithBlend(SpectatingActor, 1.5f);
			}
		}	
	}
}