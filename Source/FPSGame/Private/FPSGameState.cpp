// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bIsMissionSuccess)
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
    {
        AFPSPlayerController* PlayerController = Cast<AFPSPlayerController>(It->Get());
        if (PlayerController && PlayerController->IsLocalController())
        {
            PlayerController->OnMissionCompleted(InstigatorPawn, bIsMissionSuccess);

            APawn* ControlledPawn = PlayerController->GetPawn();
            if (ControlledPawn)
            {
                ControlledPawn->DisableInput(PlayerController);
            }

            if (bIsMissionSuccess)
            {
                UGameplayStatics::PlaySoundAtLocation(this, MissionCompleteSuccessSound, InstigatorPawn->GetActorLocation(),FMath::Clamp<float>(MissionCompleteSuccessSoundVolume, 0.f, 1.f));	
            }
            else
            {
                UGameplayStatics::PlaySoundAtLocation(this, MissionCompleteFailedSound, InstigatorPawn->GetActorLocation(),FMath::Clamp<float>(MissionCompleteSuccessSoundVolume, 0.f, 1.f));	
            }
        }
    }
}
