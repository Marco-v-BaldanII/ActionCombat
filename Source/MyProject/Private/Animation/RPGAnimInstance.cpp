// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RPGAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h" // required for GetMovementComponent()
#include "../Public/RPGCharacter.h" // hovering over a class in the contentObserver will show its include path

void URPGAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {


	ARPGCharacter* owningActor = Cast<ARPGCharacter>(GetOwningActor());

	if (IsValid(owningActor)) {
		float Speed = owningActor->GetVelocity().Size();
		ForwardSpeed = owningActor->Direction.Y * Speed;
		SideSpeed = owningActor-> Direction.X * Speed;

		isFalling = owningActor->GetMovementComponent()->IsFalling();
	}

}



