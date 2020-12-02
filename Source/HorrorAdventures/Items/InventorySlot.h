// Copyright Pranav 2020

#pragma once

#include "CoreMinimal.h"
class AItemActor;


/**
 * 
 */
class HORRORADVENTURES_API InventorySlot
{
public:
	InventorySlot();
	~InventorySlot();

	AItemActor* Item;

	bool bIsFree;

	void UseSlotItem();

	void AddItemToSlot(AItemActor* ActorToAdd);


private:

	class APlayerCharacter* PlayerCharacter;

};
