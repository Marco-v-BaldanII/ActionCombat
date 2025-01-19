// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SwordAnimNotifyState.generated.h"

/**
 * 
 */


UENUM()
enum EComboSections {
	// Sections defined in the Great Sword Slash Montage
	None UMETA(DisplayName = "None"),
	HorizontalSlash UMETA(DisplayName = "HorizontalSlash"),
	DiagonalSlash UMETA(DisplayName = "DiagonalSlash"),
	JumpAttack UMETA(DisplayName = "JumpAttack"),
	SlideAttack UMETA(DisplayName = "SlideAttack"),
	RotateSlash UMETA(DisplayName = "RotateSlash")

};


UCLASS()
class MYPROJECT_API USwordAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	// EditAnywhwere is required for editing its values, otherwise it won't show up in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	TEnumAsByte<EComboSections> NextLightComboSection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	TEnumAsByte<EComboSections> NextHeavyComboSection;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
