// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTChooseNextWaypoint.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "FPSGuard.h"

EBTNodeResult::Type UBTTChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* AIControlledPawn = AIController->GetPawn();
    AFPSGuard* AIGuardPawn = Cast<AFPSGuard>(AIControlledPawn);

    if (!AIGuardPawn) return EBTNodeResult::Failed;

    const TArray<AActor*> PatrolPoints = AIGuardPawn->GetPatrolPoints();

    if (PatrolPoints.Num() <= 0) return EBTNodeResult::Failed;

    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    const int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
    BlackboardComponent->SetValueAsObject(NextWaypoint.SelectedKeyName, PatrolPoints[Index]);
    
    const int32 NextIndex = (1 + Index) % PatrolPoints.Num();
    BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
    
    return EBTNodeResult::Succeeded;
}
