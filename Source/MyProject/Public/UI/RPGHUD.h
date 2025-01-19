// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StaminaWidget.h"
#include "RPGHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ARPGHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDEfaultsOnly, Category = "Widgets")
	// a variable that stores a class "id" of a class that derives from UUserWidget
	TSubclassOf<UUserWidget> StaminaBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UStaminaWidget* StaminaBarWidget;

protected:
	void AddStaminaBarWidget();

	virtual void BeginPlay() override;

};
