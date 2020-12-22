// Copyright Pranav 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HORRORADVENTURES_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	virtual void BeginPlay() override;
	
	
};