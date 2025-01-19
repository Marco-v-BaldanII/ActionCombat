// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	FVector velocity = GetOwningActor()->GetVelocity();
	FRotator rotation = GetOwningActor()->GetActorRotation();

	ForwardSpeed = velocity.Size();
	// Built in method to calculate the angle between vector and a forward orientation
	Direction = CalculateDirection(velocity, rotation);
}