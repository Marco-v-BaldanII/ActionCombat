// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorCharacter.h"
#include "Inventory/SwordEquipment.h"
#include "Inventory/Sword.h"
#include "Kismet/KismetMathLibrary.h"

AWarriorCharacter::AWarriorCharacter() : Super()
{
	RightHandWeapon = CreateDefaultSubobject<USwordEquipment>(TEXT("RightHandWeapon"));
	// Attach the melee weapon to the socket of the Mesh component
	//                               mesh     , socket name
	RightHandWeapon->SetupAttachment(GetMesh(), "WeaponRestSocket");
	IsRightHandWeaponLoaded = false;
	CurrentComboType = EComboTypes::Empty;
}

void AWarriorCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWarriorCharacter::BeginPlay() {
	// It's required to call the parent's BeginPlay
	Super::BeginPlay();

	// Create the great sword object
	if (IsValid(GreatSwordClass)) /* if (the weapn bp set up in the warrior bp ) is valid */ {

		ASword* greatSword = NewObject<ASword>(GetWorld(), GreatSwordClass);

		if (greatSword) {
			// Assign the great sword
			RightHandWeapon->Equipment = greatSword;
			// Set the skeletal mesh of the component
			RightHandWeapon->SetSkeletalMesh(greatSword->Mesh->GetSkeletalMeshAsset());
		}
	}

	const FTransform swordRestTransform(WeaponRestRotation);
	// Mount the great sword at the back of the character
	RightHandWeapon->SetRelativeTransform(swordRestTransform);
}

void AWarriorCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AWarriorCharacter::LightAttack(const FInputActionValue& value) {

	// Face target
	FRotator targetRot;
	// if any target is locked
	if (currentTarget) {
		// Find the rotation for the player at the start location to the point at the target location
		targetRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), currentTarget->GetActorLocation());

		GetWorld()->GetFirstPlayerController()->SetControlRotation(targetRot);
	}


	IsAttacking = true;

	// if the sword is not laoded yet
	if (!IsRightHandWeaponLoaded) {
		// Set the current combo type
		CurrentComboType = EComboTypes::LightMelee;
		// Play the draw a sowrd montage
		if (IsValid(DrawASwordMontage)) {
			PlayAnimMontage(DrawASwordMontage);
		}
	}
		// if the sword attack montage is not playing yet
	else if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GreatSwordSlashMontage) == false) {

		if (IsValid(GreatSwordSlashMontage)) {

			FText sectionName;
			const UEnum* EnumPtr = FindFirstObjectSafe<UEnum>(TEXT("EComboSections"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("DefaultLightSlashSection %d"), DefaultLightSlashSection));
			// Get the default light atk section name
			if (EnumPtr) {
				sectionName = EnumPtr->GetDisplayNameTextByValue(DefaultLightSlashSection);
			}
			// Play the default ligth attack
			PlayComboMontage(FName(sectionName.ToString()));
		}
		}
	
	else /* Otherwise start combo */ {
		NextComboType = EComboTypes::LightMelee;
	}
	
}

void AWarriorCharacter::HeavyAttack(const FInputActionValue& value) {

	FRotator targetRot;

	if (currentTarget) {
		targetRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), currentTarget->GetActorLocation());
		GetWorld()->GetFirstPlayerController()->SetControlRotation(targetRot);
	}



	IsAttacking = true;

	// if the sword is not laoded yet
	if (!IsRightHandWeaponLoaded) {
		// Set the current combo type
		CurrentComboType = EComboTypes::HeavyMelee;
		// Play the draw a sowrd montage
		if (IsValid(DrawASwordMontage)) {
			PlayAnimMontage(DrawASwordMontage);
		}
	}
	else if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GreatSwordSlashMontage) == false) {

		if (IsValid(GreatSwordSlashMontage)) {

			FText sectionName;
			const UEnum* EnumPtr = FindFirstObjectSafe<UEnum>(TEXT("EComboSections"));

			// Get the default light atk section name
			if (EnumPtr) {
				sectionName = EnumPtr->GetDisplayNameTextByValue(DefaultHeavySlashSection);
			}
			// Play the default ligth attack
			auto t = FName(TEXT("JumpAttack"));
			PlayComboMontage(FName(/*TEXT("JumpAttack")*/ FName(sectionName.ToString())));
		}
	}
	
	else /* Otherwise start combo */ {
		NextComboType = EComboTypes::HeavyMelee;
	}
	
}

bool AWarriorCharacter::IsSectionValid(UAnimMontage* Montage, FName SectionName)
{
	if (Montage == nullptr) return false;

	// Get the list of sections in the montage
	TArray<FAnimMontageInstance> Instances;
	//auto a = GetMesh()->GetAnimInstance()->GetActiveMontageInstance()->GetCurrentSection();



	return false; // Section does not exist
}

void AWarriorCharacter::PlayComboMontage(FName section, UAnimMontage* montage, float rate) {
	// Play the specified section in the montage
	if (IsValid(montage)) { 
		// method from ACharacter class
		PlayAnimMontage(montage, rate, section);
	}
	else {

		PlayAnimMontage(GreatSwordSlashMontage, rate, section);
	}
}

void AWarriorCharacter::EquipAGrateSword() {
	//Load the great sword
	RightHandWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHandSwordSocket");

	const FTransform swordMountTransform(RightHandWeaponMountRotation);
	RightHandWeapon->SetRelativeTransform(swordMountTransform);

	IsRightHandWeaponLoaded = true;
}

void AWarriorCharacter::UnloadAGreatSword() {
	
	if (IsRightHandWeaponLoaded) {

		RightHandWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponRestSocket");
		const FTransform swordMountTransform(WeaponRestRotation);
		RightHandWeapon->SetRelativeTransform(swordMountTransform); //CHANGE o rest

		IsRightHandWeaponLoaded = false;
	}
}

void AWarriorCharacter::DrawAGreatSwordNotify() {
	// If the sword is not loaded and we're playing the attack montage
	if (!IsRightHandWeaponLoaded && CurrentComboType != EComboTypes::Empty) {

		EquipAGrateSword();

		// Determine which combo to play, heavy or light
		if (CurrentComboType == EComboTypes::LightMelee) {
			LightAttack(0);
		}
		else if (CurrentComboType == EComboTypes::HeavyMelee) {
			HeavyAttack(0);
		}
		//Reset current atk to empty
		CurrentComboType = EComboTypes::Empty;
	}
}

void AWarriorCharacter::UnloadAGreatSwordNotify(bool playMontage) {

	if (IsRightHandWeaponLoaded) {
		if (playMontage && IsValid(UnloadSwordMontage)) {
			// unload sword to transition to idle/walk
			PlayAnimMontage(UnloadSwordMontage);
		}
		else {
			// The montage is playing, unlaod the sword directly
			UnloadAGreatSword();
		}
	}
}