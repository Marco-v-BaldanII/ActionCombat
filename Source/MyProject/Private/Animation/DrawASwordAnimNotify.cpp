// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DrawASwordAnimNotify.h"
#include "WarriorCharacter.h"

// The method UDrawASwordAnimNotify::Notify is invoked when the animation in which the UDrawASwordAnimNotify is placed reaches the frame where this specific notify is triggered.

/*
Unreal Engine allows you to attach Animation Notifies (AnimNotifies) to specific frames of an animation. 
These notifies are markers that trigger specific events or logic during the playback of the animation.
*/
void UDrawASwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	// Get the warrior character from the mesh component's owner actor

	AWarriorCharacter* warrior = Cast<AWarriorCharacter>(MeshComp->GetOwner());

	if (warrior) {
		warrior->DrawAGreatSwordNotify();
	}
}