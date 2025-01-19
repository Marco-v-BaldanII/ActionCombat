// Fill out your copyright notice in the Description page of Project Settings.


#include "Stats/DiceRoll.h"

UDiceRoll::UDiceRoll() {
	// Default normal die with 6 faces, roll once
	Rolls = 1;
	Faces = 6;
	Modifier = 0;
}

UDiceRoll::UDiceRoll(int rolls, int faces, int modifier) {
	Rolls = rolls;
	Faces = faces;
	Modifier = modifier;
}

int UDiceRoll::Die(int rolls, int faces, int modifier) {

	int total = 0;

	// Roll a die several times
	for (int i = 0; i <= rolls; ++i) {
		// Accumulate the outcomes
		total += FMath::RandRange(1, faces);
	}

	// Apply the modifier
	return total + modifier;

}

int UDiceRoll::Roll() {
	return Die(Rolls, Faces, Modifier);
}