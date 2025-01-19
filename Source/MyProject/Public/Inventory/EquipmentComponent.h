// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "EquipmentComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEquipmentComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	// Refer to the equipment component
	UPROPERTY()
	class AMyEquipment* Equipment;
	bool isEquipped;
	
};
