// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipmentStat.generated.h"

/**
 * 
 */
// DefaultToInstanced = whenever something has a ptr to a UEquipment unrel will automatically fill in the value with a new instance of UEquipment
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew )
class MYPROJECT_API UEquipmentStat : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Instanced, EditAnywhere, Category = "Stats")
	// here having 'class' keyword serves as a forward declaration
	class UDiceRoll* DefensePower;
	
};
