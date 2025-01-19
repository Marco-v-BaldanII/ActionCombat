// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DiceRoll.generated.h"

/**
 * 
 */
// Blueprintable = you can create Blueprint classes derived from this C++ class
// EditInLineNew = class can be instantiated and edited directly inside the editor through property panels.
UCLASS(Blueprintable, EditInlineNew)
class MYPROJECT_API UDiceRoll : public UObject
{
	GENERATED_BODY()

public:
	UDiceRoll();
	UDiceRoll(int rolls, int faces, int modifier);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DiceRoll")
	int Rolls;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DiceRoll")
	int Faces;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DiceRoll")
	int Modifier;

	static int Die(int rolls, int faces, int modifier = 0);
	int Roll();
	
};
