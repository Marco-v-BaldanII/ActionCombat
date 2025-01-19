// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "StaminaWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
//	UProgressBar* StaminaBar;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxStamina;

	UFUNCTION()
	// Resize the stamina bar by setting the percent value
	void ResizeStaminaBar(float percent);

	void SetStamina(int stamina);

	void SetMaxStamina(int maxStamina);

};
