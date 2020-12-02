// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class HORRORADVENTURES_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere, Category = "Function")
	float HealthToHeal;

	UPROPERTY(EditAnyWhere, Category = "Description")
	FString Description;

	virtual void Use(ACharacter* CallingCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	class UTexture2D* Image;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ACharacter* CallingCharacter);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components",meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Usage")
	bool bShouldBeDestroyedOnUse;

	
	



	
	

	
};




