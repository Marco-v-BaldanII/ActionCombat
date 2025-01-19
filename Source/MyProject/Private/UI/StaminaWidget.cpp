// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StaminaWidget.h"


void UStaminaWidget::ResizeStaminaBar(float percent) {
	// Resize the stamina bar by setting the percent value
	StaminaBar->SetPercent(percent);
}

void UStaminaWidget::SetStamina(int stamina) {
	// set the text block's text
	Stamina->SetText(FText(FText::FromString(FString::FromInt(stamina))));
}

void UStaminaWidget::SetMaxStamina(int maxStamina) {

	// Set the text of the MaxStamina block
	MaxStamina->SetText(FText::FromString(FString::FromInt(maxStamina)));
}