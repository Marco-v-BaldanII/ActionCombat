// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/MyItem.h"
#include "MyEquipment.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyEquipment : public AMyItem
{
	GENERATED_BODY()

public:
	UPROPERTY(Instanced, EditAnywhere, Category = "Stats")
	class UEquipmentStat* Stats; // every equipment piece has a instance of equipment class


	
};
