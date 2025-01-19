// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Health.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT_API IHealth
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// For a INTERFACE , pure virtual methods (=0) are required

	virtual void ApplyDamage(int damageValue, AActor* owner) = 0;
	virtual bool IsDead() = 0;

};
