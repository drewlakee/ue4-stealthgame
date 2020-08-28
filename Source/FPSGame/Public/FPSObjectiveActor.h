// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	float DeltaAtZ = 0.f;
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffect() const;
	void FlowInDeltaHeight(float DeltaTime);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup Effects")
	UParticleSystem* PickupEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup Sounds")
	USoundBase* PickupSound;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup Sounds")
	float PickupSoundVolume = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Flow")
	float FlowBound = 0.f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
