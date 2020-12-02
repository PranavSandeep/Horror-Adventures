// Copyright Pranav 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSlotActor.generated.h"

UCLASS()
class HORRORADVENTURES_API AItemSlotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSlotActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory",  meta = (AllowPrivateAccess = "true"))
	bool bIsfree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory",  meta = (AllowPrivateAccess = "true"))
	class AItemActor* SlotItem;

	void UseItem();

	void PickUpItem(AItemActor* ActorToPickUp);

	void DropItem();

};
