// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class HORRORADVENTURES_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthToHeal;

	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Appearance", BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	virtual void Use(ACharacter* UsingCharacter);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ACharacter* UsingCharacter);

	
	
};
