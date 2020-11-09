// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"

UItem::UItem()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
}

void UItem::Use(ACharacter* UsingCharacter)
{
    
}
