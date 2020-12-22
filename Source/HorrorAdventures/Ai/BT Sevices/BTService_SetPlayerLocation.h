// Copyright Pranav 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class HORRORADVENTURES_API UBTService_SetPlayerLocation : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetPlayerLocation();

	protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};

	

