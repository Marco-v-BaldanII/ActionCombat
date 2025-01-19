// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stats/EquipmentStat.h"
#include "WeaponStats.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UWeaponStats : public UEquipmentStat
{
	GENERATED_BODY()

public:
	// -Instanced is like DefaultToInstanced butfor a concrete property, this UDiceRoll is initialized to a new instance fo UDiceRoll by default, it won't be nullptr
	UPROPERTY(Instanced, EditAnywhere, Category = "Stats")
	class UDiceRoll* AttackPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float AttackRate = 1.0f;
};
