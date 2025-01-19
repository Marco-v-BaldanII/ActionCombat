// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/EquipmentComponent.h"
#include "SwordEquipment.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USwordEquipment : public UEquipmentComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();
	
};
