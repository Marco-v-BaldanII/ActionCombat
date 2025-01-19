// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatsModifier.generated.h"

UENUM() // allows to create an enum that will be shown in the unreal editor
enum EModifierTypes {

	Add UMETA(DisplayName = "Add"),
	Multi UMETA(DisplayName = "Multi")
};

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew )
class MYPROJECT_API UStatsModifier : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Type" )
	TEnumAsByte<EModifierTypes> Type; // isntance of enum

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Map")
	// this dictionary stores how much this modifier changes each stat
	TMap<FString, float> ModifierValues; 
};
