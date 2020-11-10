// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AUnlockedDoor;
class UPhysicsHandleComponent;
class UInventoryComponents;

UCLASS()
class HORRORADVENTURES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
    void MoveForward(float val);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UInventoryComponents* Inventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AActor* ActiveActor;



private:

	void SearchForUnlockedDoor();

	void Grab();

	void Release();

	void MoveSideWays(float val);

	void AddToInventory();

	void SetActiveItem();

	UPROPERTY(EditAnywhere)
	float reach = 50;

	UPROPERTY(EditAnywhere)
	float GrabReach = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* HoldPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory",  meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AItemActor> ItemActor;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;



	
	

	
	

};
