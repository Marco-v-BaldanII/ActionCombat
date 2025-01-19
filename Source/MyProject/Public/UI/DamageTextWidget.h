// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DamageText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FloatingDamageText;

	void SetDamageText(FText damage);
	void PlayFloatingTextAnimation();
	
};
