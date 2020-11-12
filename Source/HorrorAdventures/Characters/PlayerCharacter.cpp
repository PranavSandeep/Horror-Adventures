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

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoldPoint = CreateDefaultSubobject<USceneComponent>(FName("Hold Point"));

	GripPoint = CreateDefaultSubobject<USceneComponent>(FName("Grip Point"));
	GripPoint->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = FindComponentByClass<UPhysicsHandleComponent>();

	Inventory = FindComponentByClass<UInventoryComponents>();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	FHitResult Hit;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FCollisionQueryParams TraceParams = FCollisionQueryParams(TEXT(""), false, GetOwner());
		
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * GrabReach;


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

	//PlayerInputComponent->BindAction("Get First Inventory Item", IE_Pressed, this, &APlayerCharacter::SetActiveItem);

	PlayerInputComponent->BindAction("Release", IE_Pressed, this, &APlayerCharacter::Release);

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
		PhysicsHandle->ReleaseComponent();
	}

if(Inventory->Inventory.IsValidIndex(0))
{
	auto ZeroActor = Inventory->Inventory[0];

	Inventory->Inventory.Remove(ZeroActor);
}
	
}	

		

	


	


void APlayerCharacter::MoveSideWays(float val)
{
	FVector const MoveDirection = GetActorRightVector();

	AddMovementInput(MoveDirection, val);
}

void APlayerCharacter::AddToInventory()
{
	if(Inventory!=nullptr)
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

				if(Inventory != nullptr)
				{
					Inventory->AddItem(HitActor);

					HitActor->Mesh->DestroyComponent();

					if(Inventory->Inventory.Num() == 1)
					{
						SetActiveItem(HitActor);

					}

					

				}

				
				
			}
				
		}
	}
}

void APlayerCharacter::SetActiveItem(AItemActor* ItemToSet)
{
	
			if(ItemToSet != nullptr)
			{
		
				FActorSpawnParameters SpawnInfo;
		
				AItemActor* SpawnedActor = GetWorld()->SpawnActor<AItemActor>(ItemToSet->GetClass(), GripPoint->GetComponentLocation(),GripPoint->GetComponentRotation(), SpawnInfo);

				ActiveActor = SpawnedActor;
				
				PhysicsHandle->GrabComponent(SpawnedActor->Mesh, NAME_None, SpawnedActor->GetActorLocation(), true);
			}
		


	
}



	
	






