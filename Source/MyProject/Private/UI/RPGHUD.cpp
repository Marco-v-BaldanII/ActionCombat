// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGHUD.h"

void ARPGHUD::BeginPlay() {
	Super::BeginPlay();

	AddStaminaBarWidget();
}


void ARPGHUD::AddStaminaBarWidget() {
	if (IsValid(StaminaBarWidgetClass)) {
		// Create the stamina bar widget
		//                          derived widget type, world ,   TSubclassOf<UUserWidget>
		StaminaBarWidget = CreateWidget<UStaminaWidget>(GetWorld(), StaminaBarWidgetClass);

		// Add stamina bar to the viewport
		if (StaminaBarWidget) {
			StaminaBarWidget->AddToViewport();
		}
	}
}