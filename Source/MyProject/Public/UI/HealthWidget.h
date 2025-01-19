// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	// This tells Unreal Engine to bind the HealthBar variable to a ProgressBar widget in the User Widget Blueprint that has the exact same name: HealthBar
	UProgressBar* HealthBar;

	UFUNCTION() // Callable through blueprint
	void ResizeHealthBar(float percent);
	
};
