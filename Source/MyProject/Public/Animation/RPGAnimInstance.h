// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API URPGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float ForwardSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float SideSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	bool isFalling;

	// method that gets called when the anim is playing by the UAnimInstance class
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
