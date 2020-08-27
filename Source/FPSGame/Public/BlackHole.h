// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void DestroyOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* KernelSphereComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KernelMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* AttachSphereComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
