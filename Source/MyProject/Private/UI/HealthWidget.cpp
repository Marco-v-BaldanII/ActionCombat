// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthWidget.h"

void UHealthWidget::ResizeHealthBar(float percent) {
	// Use SetPercent() instead of assgn value to the percent
	HealthBar->SetPercent(percent);
}
