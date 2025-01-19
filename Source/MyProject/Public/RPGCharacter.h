// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "CharacterStats.h"
#include "UI/RPGHUD.h"
#include "Components/BoxComponent.h"
#include "RPGCharacter.generated.h" // this generated file must be the last include for some reason

UCLASS()
class MYPROJECT_API ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyLock")
	UBoxComponent* EnemyLockBox;

	UFUNCTION()
	void OnLockBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLockBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AActor* currentTarget;


	UPROPERTY(Instanced, EditAnywhere, Category = "Stats") /* Instanced indicates that we can edit the Stats property in the editor , in this case add entries to the stats dictionary*/
	UCharacterStats* Stats;

	// PlayerFollowCamera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* FollowCamera;

	// Spring arm component to follow the camera behind the player (control zoom in and zoom out )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction")
	FVector2D Direction;


	// A ptr to the input mapping context 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ZoomAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LightAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* HeavyAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DismountAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* CastFireballAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zoom")
	int ZoomSpeed = 20;

	// methods to be bound to the input actions
	void Move(const FInputActionValue& value);
	void DoubleJump(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Zoom(const FInputActionValue& value);

	void ShiftKey(const FInputActionValue& value);
	void Interact(const FInputActionValue& value);

	virtual void LightAttack(const FInputActionValue& value);
	virtual void HeavyAttack(const FInputActionValue& value);
	virtual void Dismount(const FInputActionValue& value);
	virtual void PlayCastFireballMontage(const FInputActionValue& value);



	// Third person camera controller //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseLook")
	float MaxMousePitch = 80.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseZoom")
	float MinTargetArmLenght = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MouseZoom")
	float MaxTargetArmLength = 800.0f;

	// Controll the zooming of the camera
	void MouseZoom(float val);
	// Add input (affecting Yaw) to the Controller's ControlRotation
	virtual void AddControllerYawInput(float Val) override;
	// Add input (affecting Pitch) to the Controller's ControlRotation
	virtual void AddControllerPitchInput(float Val) override;


	// Moving the player Character
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float WalkSpeed = 300.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float RunSpeed = 1200.0f;
	// Functions to bind the movement to the axis
	void MoveForward(float axis);
	void MoveBackward(float axis);
	void MoveRight(float axis);
	void MoveLeft(float axis);
	// Set movement Speed
	void Walk();
	void Sprint();

	UPROPERTY(EditDefaultsOnly, Category = "Jump")
	int MaxJumpCount = 2;
	int jumpCount = 0;
	// Override the bult in landed method
	void Landed(const FHitResult& Hit) override;

	//-------------Sprint stuff----------------//

	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	bool IsSprinting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Constraints")
	float SprintCost = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float StaminaRecoveryRate = 0.2f;

	ARPGHUD* RPGHUD;
	FTimerHandle SprintDrainTimerHandle;
	FTimerHandle RegenerateStaminaTimerHandle;

	UFUNCTION() // enables them to be called from Blueprints
	void SprintDrain();
	UFUNCTION()
	void RegenerateStamina();
	// Stop the timer for regenerating the stamina
	void ClearTimer();
	// Restart the timer for regenerating the stamina
	void RestartTimer();
	void UpdateStaminaUI(int stamina, int maxStamina = 0);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
