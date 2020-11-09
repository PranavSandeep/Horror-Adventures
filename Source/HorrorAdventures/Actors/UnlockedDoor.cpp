// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockedDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AUnlockedDoor::AUnlockedDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	RootComponent = DoorFrame;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AUnlockedDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnlockedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

