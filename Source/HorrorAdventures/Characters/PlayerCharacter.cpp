// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "AssetTypeCategories.h"
#include "InputCoreTypes.h"
#include "Components/InputComponent.h"
#include "HorrorAdventures/Actors/UnlockedDoor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "HorrorAdventures/Components/InventoryComponents.h"
#include "HorrorAdventures/Actors/ItemActor.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsChaos/ImmediatePhysicsCore_Chaos.h"
#include "Kismet/GameplayStatics.h"
#include "HorrorAdventures/Actors/ItemSlotActor.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GripPoint = CreateDefaultSubobject<USceneComponent>(FName("Grip Point"));
	GripPoint->SetupAttachment(this->GetMesh());

	
	

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = FindComponentByClass<UPhysicsHandleComponent>();

	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PhysicsHandle !=nullptr)
	{
		if(PhysicsHandle->GrabbedComponent)
		{
			PhysicsHandle->SetTargetLocation(GripPoint->GetComponentLocation());
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward", this, &APlayerCharacter::MoveForward);

	PlayerInputComponent->BindAxis("Move SideWays", this, &APlayerCharacter::MoveSideWays);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Open Door", IE_Pressed, this, &APlayerCharacter::SearchForUnlockedDoor);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Add to inventory", IE_Pressed, this, &APlayerCharacter::AddToInventory);

	PlayerInputComponent->BindAction("Release", IE_Pressed, this, &APlayerCharacter::Release);

	PlayerInputComponent->BindAction("Use Item", IE_Pressed, this, &APlayerCharacter::UseItem);



}

void APlayerCharacter::MoveForward(float val)
{
	FVector const Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, val);

	
}

void APlayerCharacter::SearchForUnlockedDoor()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	FHitResult Hit;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FCollisionQueryParams TraceParams = FCollisionQueryParams(TEXT(""), false, GetOwner());
		
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0, 0, 0);
	
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility, TraceParams);

	if(bSuccess)
	{
		AActor* HitActor = Hit.GetActor();
		
		AUnlockedDoor* Door =  Cast<AUnlockedDoor>(HitActor);

		if(Door!= nullptr)
		{
			Door->OpenDoor();
		}

		
	}
}

void APlayerCharacter::Grab()
{

	UE_LOG(LogTemp, Warning, TEXT("Works"))
	
	if(PhysicsHandle !=nullptr)
	{
		
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

		FHitResult Hit;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

		FCollisionQueryParams TraceParams = FCollisionQueryParams(TEXT(""), false, GetOwner());
		
		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * GrabReach;
	
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewPointLocation, LineTraceEnd, ECC_PhysicsBody, TraceParams);

		if(bSuccess)
		{
			PhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, Hit.GetComponent()->GetOwner()->GetActorLocation());
		}
	}

}

void APlayerCharacter::Release()
{

	if(PhysicsHandle !=nullptr)
	{
		if(PhysicsHandle->GrabbedComponent != nullptr)
		{
			PhysicsHandle->ReleaseComponent();

			bIsFree = true;
		}

		

		
		
	}

	
}

void APlayerCharacter::MoveSideWays(float val)
{
	FVector const MoveDirection = GetActorRightVector();

	AddMovementInput(MoveDirection, val);
}

void APlayerCharacter::AddToInventory()
{
	if(bIsFree)
	{
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

		FHitResult Hit;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

		FCollisionQueryParams TraceParams = FCollisionQueryParams(TEXT(""), false, GetOwner());
		
		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * GrabReach;
	
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility, TraceParams);

		if(bSuccess)
		{
			AItemActor* HitActor = Cast<AItemActor>(Hit.Actor);

			if(HitActor != nullptr)
			{
				SetActiveItem(HitActor);

				HitActor->Mesh->DestroyComponent();

				bIsFree = false;

					
			}

				
				
		}
				
	}
}


void APlayerCharacter::UseItem()
{
	if(ActiveActor != nullptr)
	{
		AItemActor* ActiveItem = Cast<AItemActor>(ActiveActor);

		if(ActiveItem != nullptr)
		{
			ActiveItem->Use(this);
			ActiveItem->OnUse(this); //BP Implementation

			if(ActiveItem->bShouldBeDestroyedOnUse)
			{
				ActiveActor->Destroy();

				bIsFree = true;
			}
			
		}
	}
}


void APlayerCharacter::SetActiveItem(AItemActor* ItemToAdd)
{

	if(ItemToAdd != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("First Actor is not nullptr"))
		
		FActorSpawnParameters const SpawnInfo;  //const because it wants me to
		
		SpawnedActor = GetWorld()->SpawnActor<AItemActor>(ItemToAdd->GetClass(), GripPoint->GetComponentLocation(), GripPoint->GetComponentRotation(), SpawnInfo);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemToAdd->Description)

		ActiveActor = SpawnedActor;

		PhysicsHandle->GrabComponent(SpawnedActor->Mesh, NAME_None, SpawnedActor->GetActorLocation(), true);
		

			


	}

	
	

	
	}

void APlayerCharacter::AddToInventorySlot()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	FHitResult Hit;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FCollisionQueryParams TraceParams = FCollisionQueryParams(TEXT(""), false, GetOwner());
		
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * GrabReach;
	
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility, TraceParams);

	if(bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Success!"))

		AItemActor* SlotActor = Cast<AItemActor>(Hit.Actor);

		if(SlotActor != nullptr)
		{
			Slot1->SlotItem = SlotActor;
		}

		

		
		
	}

}



	
	





