// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordAnimNotifyState.h"
#include "WarriorCharacter.h"

// called when the animation ends
void USwordAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {

	AWarriorCharacter* warrior = Cast<AWarriorCharacter>(MeshComp->GetOwner());

	if (warrior) {
		// If we have the next combo to play
		if (warrior->NextComboType != EComboTypes::Empty) {
			FText sectionName;
			// Get the montage
			UAnimMontage* montage = Cast<UAnimMontage>(Animation);
			// Find the enum type object
			const UEnum* EnumPtr = FindFirstObjectSafe<UEnum>(TEXT("EComboSections")); // inquire into how this works

			// Play next combo
			switch (warrior->NextComboType) {
			case EComboTypes::LightMelee:
				if (EnumPtr) {
					sectionName = EnumPtr->GetDisplayNameTextByValue(NextLightComboSection); // convert enum index to name
				}
				if (montage) {
					warrior->PlayComboMontage(FName(sectionName.ToString()), montage);
				}
				break;
			case EComboTypes::HeavyMelee:
				if (EnumPtr) {
					sectionName = EnumPtr->GetDisplayNameTextByValue(NextHeavyComboSection);
				}
				if (montage) {
					warrior->PlayComboMontage(FName(sectionName.ToString()), montage );
				}
				break;
			}
			// Reset the next combo
			warrior->NextComboType = EComboTypes::Empty;

		}
		else {
			// no combo to play, reset the IsAttacking flag
			warrior->IsAttacking = false;
		}
	}
}