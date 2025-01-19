// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStats.h"

UCharacterStats::UCharacterStats() {

}

void UCharacterStats::SetStatValue(FString name, int value) {

	BaseStats.Emplace(name, value);
}

void UCharacterStats::AddModifier(UStatsModifier* modifier) {
	Modifiers.Add(modifier);
}

void UCharacterStats::RemoveModifier(UStatsModifier* modifier) {
	Modifiers.Remove(modifier);
}

int UCharacterStats::GetStatValue(FString name) {

	if (!BaseStats.IsEmpty() && BaseStats.Contains(name)) {
		int total = BaseStats[name];
		float multiplier = 0.0f;

		for (UStatsModifier* modifier : Modifiers) {
			if (modifier->Type == EModifierTypes::Add) {
				total += modifier->ModifierValues[name];
			}
			else {
				multiplier += modifier->ModifierValues[name];
			}

		}
		return FMath::RoundHalfFromZero(total + (total * multiplier)); /*Rounds up floats , 0.5f = 1*/
	}
	else { return 0; }
}