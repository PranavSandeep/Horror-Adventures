// Copyright Pranav 2020


#include "BTService_SetPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "AIController.h"

UBTService_SetPlayerLocation::UBTService_SetPlayerLocation() 
{
    NodeName = "Update Player Location";
}

void UBTService_SetPlayerLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector( "Last Known Player Location", PlayerPawn->GetActorLocation());

}


