// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/SwordDamageAnimNotigyState.h"
#include "WarriorCharacter.h"
#include "Inventory/Sword.h"
#include "UI/HealthWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Stats/DiceRoll.h"
#include "Inventory/SwordEquipment.h"



void USwordDamageAnimNotigyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase
	* Animation, float FrameDeltaTime) {
	AWarriorCharacter* warrior = Cast<AWarriorCharacter>(MeshComp->GetOwner());


	//if (warrior && warrior->RightHandWeapon) {

	//	// Get the traceStart and raceEnd sockets
	//	FVector traceStart = warrior->RightHandWeapon->GetSocketLocation("TraceStart");

	//	FVector traceEnd = warrior->RightHandWeapon->GetSocketLocation("TraceEnd");

	//	// The hit results :
	//	TArray<FHitResult> HitArray;
	//	// ignore the sword's owner for the sphere trace
	//	TArray<AActor*> actorsToIgnore;
	//	actorsToIgnore.Add(warrior);

	//	// Perform the sphere trace and show the trace hits in blue color
	//	
	//	bool isHit = -UKismetSystemLibrary::SphereTraceMultiForObjects(warrior->GetWorld(), traceStart, traceEnd, TraceRadius, DamageObjectTypes, false, actorsToIgnore, 
	//		EDrawDebugTrace::ForDuration, HitArray, true, FLinearColor::Red, FLinearColor::Blue, 0.1f);

	//	// if some target is hit
	//	if (isHit) {
	//		for (const FHitResult hitResult : HitArray) {
	//			IHealth* health = Cast<IHealth>(HitResult.GetActor());

	//			// Get the IHealth interface
	//			if (health && !health->isDead()) {

	//				// Obtain the hit bone's name from the result
	//				FName boneName = hitResult.BoneName;

	//				ASword* greatSword = Cast<ASword>(warrior->RightHandWeapon->Equipment);

	//				//Only apply damage if jas status

	//				if (greatSword && greatSword->Stats) {
	//					UWeaponStats* weaponStats Cast < UWEaponStats(greatSword->stats);

	//					if (warrior->Stats) {
	//						// Calculñate the total dmg for the sowrd's attack power
	//						int damage = weaponStats->AttackPower->Roll() + warrior->Stats->GetStatValue(TEXT("STR"));
	//						health->ApplyDamage(damage, warrior)
	//							;
	//					}
	//					else {
	//						// if the warrior doesn't have stats use the sword's atk power
	//						health->ApplyDamage(weaponStats->AttackPower->Roll());
	//					}

	//				}

	//			}
	//		}
	//	}

	//}

}
