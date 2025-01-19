// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageTextWidget.h"

void UDamageTextWidget::SetDamageText(FText damage) {
	DamageText->SetText(damage);
}

void UDamageTextWidget::PlayFloatingTextAnimation() {

	PlayAnimation(FloatingDamageText);
}

