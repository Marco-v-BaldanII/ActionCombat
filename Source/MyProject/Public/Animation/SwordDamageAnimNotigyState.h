// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SwordDamageAnimNotigyState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USwordDamageAnimNotigyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trace)
	// Damage radius of the sphere trace
	float TraceRadius = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trace)
	TArray<TEnumAsByte<EObjectTypeQuery >> DamageObjectTypes; // array of the enum EObjectTypeQuery

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DrameDeltaTime) override;
	
};
