// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"

#include "FPSCharacter.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bIsMissionSuccess)
{
    for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
    {
        AFPSCharacter* Character = Cast<AFPSCharacter>(It->Get());
        if (Character && Character->IsLocallyControlled())
        {
            Character->DisableInput(nullptr);
        }
    }
}
