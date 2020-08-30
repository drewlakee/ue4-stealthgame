// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractZone.h"

#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractZone::AFPSExtractZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(FName("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapComponent->SetBoxExtent(FVector(200.f));
	SetRootComponent(OverlapComponent);

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractZone::HandleOverlap);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(FName("DecalComponents"));
	DecalComponent->DecalSize = OverlapComponent->GetUnscaledBoxExtent();
	DecalComponent->SetupAttachment(OverlapComponent);
}

void AFPSExtractZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		AFPSGameMode* AfpsGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		
		if (AfpsGameMode)
		{
			if (PlayerCharacter->bIsCaringObjective)
			{
				PlayerCharacter->bIsCaringObjective = false; // mission complete and objective reached end zone
		
				UGameplayStatics::PlaySoundAtLocation(this, ExtractZoneReachedSound, GetActorLocation(),FMath::Clamp<float>(ExtractZoneReachedSoundVolume, 0.f, 1.f));	

				AfpsGameMode->CompleteMission(PlayerCharacter, true);	// mission success complete
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this, ExtractZoneWrongSound, GetActorLocation(),FMath::Clamp<float>(ExtractZoneWrongVolume, 0.f, 1.f));	
			}
		}
	}
}

