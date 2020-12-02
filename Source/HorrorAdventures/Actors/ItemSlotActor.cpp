// Copyright Pranav 2020


#include "ItemSlotActor.h"
#include "HorrorAdventures/Actors/ItemActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItemSlotActor::AItemSlotActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSlotActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemSlotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSlotActor::UseItem()
{
	SlotItem->Use(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SlotItem->OnUse(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)); //BP Implementation
}

void AItemSlotActor::PickUpItem(AItemActor* ActorToPickUp)
{
	SlotItem = ActorToPickUp;
}

void AItemSlotActor::DropItem()
{
	SlotItem = nullptr;
}

