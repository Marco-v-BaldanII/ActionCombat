// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "SwordAnimNotifyState.h" // should be in animation folder
#include "WarriorCharacter.generated.h"

UENUM()
enum EComboTypes {
	Empty UMETA(DisplayName = "Empty"),
	LightMelee UMETA(DisplayName = "LightMelee"),
	HeavyMelee UMETA(DisplayName = "HeavyMelee")
};

UCLASS()
class MYPROJECT_API AWarriorCharacter : public ARPGCharacter
{
	GENERATED_BODY()
	
public:


	AWarriorCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//-----------Animation stuff-----------//

	// EditDefaultsOnly is required to assign the montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montages")
	UAnimMontage* GreatSwordSlashMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	TEnumAsByte<EComboSections> DefaultLightSlashSection; // section in the montage

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	TEnumAsByte<EComboSections> DefaultHeavySlashSection;

	TEnumAsByte<EComboTypes> NextComboType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	bool IsAttacking = true;

	virtual void PlayComboMontage(FName section, UAnimMontage* montage = 0, float rate = 1.0f);

	virtual void LightAttack(const FInputActionValue& value) override;
	virtual void HeavyAttack(const FInputActionValue& value) override;

	bool IsSectionValid(UAnimMontage* Montage, FName SectionName);

	// Sword attachment stuff

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AMyItem> GreatSwordClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool IsRightHandWeaponLoaded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class USwordEquipment* RightHandWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FRotator WeaponRestRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FRotator RightHandWeaponMountRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* DrawASwordMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* UnloadSwordMontage;
	TEnumAsByte<EComboTypes> CurrentComboType;

	void EquipAGrateSword();
	void UnloadAGreatSword();
	void DrawAGreatSwordNotify();
	// playMontage = is currently in a montage ? 
	void UnloadAGreatSwordNotify(bool playMontage);
};
