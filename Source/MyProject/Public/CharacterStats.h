// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatsModifier.h"
#include "CharacterStats.generated.h"

/**
 * 
 */ //                                   can be instnaced  from the UE editor Property window
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew) /* Expose class to create blueprints */
class MYPROJECT_API UCharacterStats : public UObject
{
	GENERATED_BODY()

public:
	UCharacterStats();

	// Base stats MaxHp, MaxMp, Streght, Speed, Intelligence
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BaseStats")
	TMap<FString, int> BaseStats;

	void SetStatValue(FString name, int value);
	
	UPROPERTY(EditDefaultsOnly, Category = "Modifiers")
	TArray<UStatsModifier*> Modifiers;

	void AddModifier(UStatsModifier* modifier);
	void RemoveModifier(UStatsModifier* modifier);
	// Gets a base stat with all modifications applied
	int GetStatValue(FString name);

};
