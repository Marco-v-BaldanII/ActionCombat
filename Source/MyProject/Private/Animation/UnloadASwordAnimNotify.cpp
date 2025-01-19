// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/UnloadASwordAnimNotify.h"
#include "WarriorCharacter.h"

void UUnloadASwordAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {

	AWarriorCharacter* warrior = Cast<AWarriorCharacter>(MeshComp->GetOwner());

	// get da montage
	UAnimMontage* unloadSwordMontage = Cast<UAnimMontage>(Animation);
	// Unload the sword when you're not attacking
	if (warrior && warrior->IsAttacking) {
		if (unloadSwordMontage) {
			// Pass in false to unload the sword montage directly
			warrior->UnloadAGreatSwordNotify(false);

		}
		else /* Not a montage, pass true to play the Montage first*/ {
			warrior->UnloadAGreatSwordNotify(true);
		}
	}

}