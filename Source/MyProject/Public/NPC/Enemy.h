// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/Health.h"
#include "CharacterStats.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemy : public ANPC , public IHealth /* Implementing the IHealth interface */
{
	GENERATED_BODY()

public:
	AEnemy();

	UPROPERTY(Instanced, EditAnywhere, Category = "Stats")
	UCharacterStats* Stats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Widgets")
	UWidgetComponent* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montages")
	TArray<UAnimMontage*> DeathMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montages")
	TArray<UAnimMontage*> GetHitMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montages")
	TArray<UAnimMontage*> AttackMontages;

	virtual void ApplyDamage(int value, AActor* causer) override;
	virtual bool IsDead() override;

	virtual void PlayDeathMontage();
	virtual void PlayHitMontage();

	void ResizeHealthBar(int hp);

private:
	bool isDead = false;
};
