// Copyright Pranav 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UBTService_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class HORRORADVENTURES_API UUBTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UUBTService_PlayerLocationIfSeen();

	protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;


	
};
