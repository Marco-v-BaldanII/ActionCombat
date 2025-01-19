// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Enemy.h"
#include "UI/DamageTextWidget.h"
#include "UI/HealthWidget.h"
#include "Components/CapsuleComponent.h"

AEnemy::AEnemy() {
	// Createand attach the HealthBar component
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBar->SetupAttachment(RootComponent);

	LockWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockWidget"));
	LockWidget->SetupAttachment(RootComponent);


	// Damage text 
	DamageText = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageTextWidget"));
	DamageText->SetupAttachment(RootComponent);

	UCapsuleComponent* CapsuleKomponent = GetCapsuleComponent();
	CapsuleKomponent->SetupAttachment(RootComponent);

	CapsuleKomponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnSwordHit); // Assuming your mesh has the collision
}

void AEnemy::OnSwordHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	ApplyDamage(3, OtherActor);
}

void AEnemy::ResizeHealthBar(int hp) {
	// Get health bar width
	UHealthWidget* healthBar = Cast<UHealthWidget>(HealthBar->GetUserWidgetObject());

	if (healthBar) {
		// Get the enmy's max hp
		int maxhp = Stats->GetStatValue("MaxHP");
		// Resize the health bar
		if (maxhp != 0) {
			healthBar->ResizeHealthBar(hp / (float)maxhp);
		}
	}
}

void AEnemy::ApplyDamage(int damageValue, AActor* causer) {

	// Get the damage text widget
	UDamageTextWidget* dmgText = Cast<UDamageTextWidget>(DamageText->GetUserWidgetObject());


	if (dmgText) {
		// Pass in the string of the damage value and set the dmg text
		dmgText->SetDamageText(FText::FromString(FString::FromInt(damageValue)));

		// Play the floating text animation
		dmgText->PlayFloatingTextAnimation();
	}


	if (Stats) {
		// Get the enemy's current hp
		int hp = Stats->GetStatValue("HP");

		// Apply the damage
		hp -= damageValue;

		// If the HP is less than 0 after the damage, reste it to 0 and set isDead

		if (hp <= 0) {
			hp = 0;
			isDead = true;
			// Play the death montage
			PlayDeathMontage();
		}
		else {
			PlayHitMontage();
		}

		ResizeHealthBar(hp);
		Stats->SetStatValue("HP", hp);
	}
}

void AEnemy::PlayDeathMontage() {

	if (DeathMontages.Num() != 0) {
		// Get a random int from 0 to array size -1
		int num = FMath::RandRange(0, DeathMontages.Num() - 1);
		// Play the montage
		PlayAnimMontage(DeathMontages[num]);
	}
}

void AEnemy::PlayHitMontage() {

	if (GetHitMontages.Num() != 0) {
		int num = FMath::RandRange(0, GetHitMontages.Num() - 1);
		PlayAnimMontage(GetHitMontages[num]);
	}
}

bool AEnemy::IsDead() {
	return isDead;
}

void AEnemy::ShowLocked(bool visible) {
	if (LockWidget) {
		LockWidget->SetVisibility(visible);
	}
}