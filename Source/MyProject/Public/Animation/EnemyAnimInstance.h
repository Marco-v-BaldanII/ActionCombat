// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/RPGAnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UEnemyAnimInstance : public URPGAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	bool IsResting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	bool IsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction")
	float Direction;
	// Store the degree of the angle between velocity amd forward rotation
	

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
