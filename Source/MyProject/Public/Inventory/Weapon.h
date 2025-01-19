// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/MyEquipment.h"
#include "Weapon.generated.h"

/**
 * 
 */
UENUM()
enum EAttackTypes {
	Melee UMETA(DisplayName = "Melee"),
	Magical UMETA(DisplayName = "Magical")
};

UCLASS()
class MYPROJECT_API AWeapon : public AMyEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TEnumAsByte<EAttackTypes> AttackType;
};
