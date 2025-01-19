// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/Lock.h"
#include "Interfaces/Health.h"

// Sets default values
ARPGCharacter::ARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instanciate components
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraCoom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	// Attach components to object :
	cameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->TargetArmLength = 300.0f;

	//----------Enemy Lock Box-------------//
	EnemyLockBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyLockBox"));
	// Attach it to the cameraBoom, not the root
	EnemyLockBox->SetupAttachment(cameraBoom);
	// Register the delegates
	EnemyLockBox->OnComponentBeginOverlap.AddDynamic(this, &ARPGCharacter::OnLockBoxBeginOverlap);

	EnemyLockBox->OnComponentEndOverlap.AddDynamic(this, &ARPGCharacter::OnLockBoxEndOverlap);

}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	GetWorld()->GetTimerManager().SetTimer(RegenerateStaminaTimerHandle, this, &ARPGCharacter::RegenerateStamina, 0.5f, true);
	RPGHUD = Cast<ARPGHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Get the player co0ntroller
	APlayerController* controller = Cast<APlayerController>(GetController());
	if (controller) {
		// Get the local player subsystem
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer());
		if(subsystem) {
			// Clear out existing mapping and add the control mapping context
			subsystem->ClearAllMappings();
			subsystem->AddMappingContext(InputMappingContext, 0);
		}

	}
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSprinting) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("sprinting ")));
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("not sprinting ")));
	}
}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent) {
		// Bind the methods to the input actions
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGCharacter::Move);
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPGCharacter::Look);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARPGCharacter::DoubleJump);
		enhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARPGCharacter::Zoom);

		enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ARPGCharacter::ShiftKey);
		enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ARPGCharacter::ShiftKey);

		enhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARPGCharacter::Interact);
		enhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &ARPGCharacter::LightAttack);
		enhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &ARPGCharacter::HeavyAttack);
		enhancedInputComponent->BindAction(DismountAction, ETriggerEvent::Triggered, this, &ARPGCharacter::Dismount);
		enhancedInputComponent->BindAction(CastFireballAction, ETriggerEvent::Triggered, this, &ARPGCharacter::PlayCastFireballMontage);
	}

}

void ARPGCharacter::Move(const FInputActionValue& value) {

	// Handle movement action
	const FVector2D moveValue = value.Get<FVector2D>();
	//----Y axis----//
	
	if (moveValue.Y > 0) {
		MoveForward(moveValue.Y);
	}
	else if (moveValue.Y < 0) {
		MoveBackward(moveValue.Y);
	}

	//----X axis----//

	if (moveValue.X > 0) {
		MoveRight(moveValue.X);
	}
	else if (moveValue.X < 0) {
		MoveLeft(moveValue.X);
	}

}
void ARPGCharacter::DoubleJump(const FInputActionValue& value) {

	// Increase the jump count
	jumpCount++;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("jump %d"), jumpCount));
	UE_LOG(LogTemp, Warning, TEXT("Jimp Count: %d"), jumpCount);
	if (jumpCount <= MaxJumpCount) {
		// JumpZVelocity is a constant in the CharacterMovement component, it can be changed here or through the blueprint
		FVector velocity = FVector(0, 0, GetCharacterMovement()->JumpZVelocity);
		// applies a velocity to the character.

		// p1 = velocity, p2 , p3 = add velocity or replace velocity
		LaunchCharacter(velocity, false, true);
	}
}
void ARPGCharacter::Look(const FInputActionValue& value) {

	// Get the position to look towards from the action value
	const FVector2D lookAxisValue = value.Get<FVector2D>();
	//Call the methods and pass in the mouse axis values
	AddControllerYawInput(lookAxisValue.X);
	AddControllerPitchInput(lookAxisValue.Y);

}
void ARPGCharacter::Zoom(const FInputActionValue& value) {

	const float zoomValue = value.Get<float>();
	// Call the mouse zoom and pass the scaled value
	MouseZoom(zoomValue);
}

void ARPGCharacter::ShiftKey(const FInputActionValue& value) {

	const bool shiftKeyPressed = value.Get<bool>();

	if (shiftKeyPressed) {
		Sprint();
	}
	else {
		// PROBLEM it doesnt enter here for some reason, the method isnt called on key release or something ?
		IsSprinting = false;
		GetWorldTimerManager().ClearTimer(SprintDrainTimerHandle);
		Walk();
	}
}
void ARPGCharacter::Interact(const FInputActionValue& value) {

}

void ARPGCharacter::LightAttack(const FInputActionValue& value) {

}
void ARPGCharacter::HeavyAttack(const FInputActionValue& value) {

}
void ARPGCharacter::Dismount(const FInputActionValue& value) {

}
void ARPGCharacter::PlayCastFireballMontage(const FInputActionValue& value) {

}

void ARPGCharacter::AddControllerYawInput(float Val) {

	if (Val != 0) {

		cameraBoom->AddRelativeRotation(FRotator(0, Val, 0));
	}

}

void ARPGCharacter::AddControllerPitchInput(float Val) {

	Super::AddControllerPitchInput(Val);

	float future_pitch = cameraBoom->GetRelativeRotation().Pitch + Val;

	float pitch = FMath::Clamp(future_pitch, -MaxMousePitch, MaxMousePitch);

	FRotator rotation = FRotator(pitch, cameraBoom->GetRelativeRotation().Yaw, 0);
	cameraBoom->SetRelativeRotation(rotation);
}

void ARPGCharacter::MouseZoom(float Val) {

	float armLength = cameraBoom->TargetArmLength + Val;

	cameraBoom->TargetArmLength = FMath::Clamp(armLength, MinTargetArmLenght, MaxTargetArmLength);
}

void ARPGCharacter::MoveForward(float axis) {
	if (axis > 0) {
		// Obtain the current Yaw rotation of the camera Boom
		float controllerYaw = cameraBoom->GetRelativeRotation().Yaw;
		// Rotate the player character towards the camera's facing direction
		GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(0, controllerYaw, 0));

		// Move the camera in their forward direction
		//              world_diection            0-1f percentage of movement applied
		AddMovementInput(GetActorForwardVector(), axis);
		// Here [0,1] means moving forward
		Direction.X = 0;
		Direction.Y = axis; // axis = 1

	}
}
void ARPGCharacter::MoveBackward(float axis) {

	if (axis < 0) {
		// Obtain the yaw rotation to the backwards of the camera by adding 180 degrees
		float controllerYaw = cameraBoom->GetRelativeRotation().Yaw + 180;
		// Turn player backwards
		GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(0, controllerYaw, 0));

		AddMovementInput(GetActorForwardVector(), -axis);
		// Here [0, -1] means moving backwards
		Direction.X = 0;
		Direction.Y = axis;

	}
}
void ARPGCharacter::MoveRight(float axis) {
	if (axis > 0) {
		// Obtainthe Yaw rotation to the right of the camera by adding 90 deg
		float controllerYaw = cameraBoom->GetRelativeRotation().Yaw + 90.0f;
		// rotate the player character towards the camera's facing direction
		GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(0, controllerYaw, 0));

		AddMovementInput(GetActorForwardVector(), axis);
		// Here [1,0] means moving to the right
		Direction.X = axis;
		Direction.Y = 0;
	}

}
void ARPGCharacter::MoveLeft(float axis) {
	if (axis < 0) {
		// Obtain the Yaw rotation to the left of the camera by subtracting 90 deg to the current yaw
		float controllerYaw = cameraBoom->GetRelativeRotation().Yaw - 90.0f;
		// Rotate the player character to face the left side of the camera
		GetWorld()->GetFirstPlayerController()->SetControlRotation(FRotator(0, controllerYaw, 0));

		// Move forward in the facing direction
		AddMovementInput(GetActorForwardVector(), -axis);
		// Here [-1,0] means left
		Direction.X = axis;
		Direction.Y = 0;
	}
}

void ARPGCharacter::Walk() {
	// Set the maximum ground speed when walking
	auto movement = GetCharacterMovement();
	movement->MaxWalkSpeed = WalkSpeed;
}
void ARPGCharacter::Sprint() {
	
	if (Stats->GetStatValue("STA") >= SprintCost) {
		auto movement = GetCharacterMovement();
		movement->MaxWalkSpeed = RunSpeed;

		IsSprinting = true;
		// Call SprintDrain                                                       every 0.5 seconds ,   starting 0 seconds from now
		GetWorldTimerManager().SetTimer(SprintDrainTimerHandle, this, &ARPGCharacter::SprintDrain, 0.5f, true, 0.0f);
	}


}

// method from ACharacter ,called automatically by the engine when a character lands on a surface after being in the air
void ARPGCharacter::Landed(const FHitResult& hit) {

	jumpCount = 0; // Reset the jumpCount
}

void ARPGCharacter::SprintDrain() {
	if (!IsSprinting) { return; }

	// Get current stamina
	int stamina = Stats->GetStatValue("STA");
	// Decrease the stamina
	stamina -= SprintCost;
	// Reset the stamina
	Stats->SetStatValue("STA", stamina);
	// Update the stamina bar
	UpdateStaminaUI(stamina);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("sprinting ")));
	if (stamina < SprintCost) /* Not enough stamina to sprint */ {
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		// Clear the time to stop the sprint drain
		GetWorldTimerManager().ClearTimer(SprintDrainTimerHandle);
		IsSprinting = false;

	}
}

void ARPGCharacter::RegenerateStamina() {
	// NOte: Must check stats otherwise could crash !

	if (!IsSprinting && Stats) {
		int stamina = Stats->GetStatValue("STA");

		if (stamina != Stats->GetStatValue("MaxSTA")) {
			// Regenerate stamina
			stamina += StaminaRecoveryRate * Stats->GetStatValue("STR");

			int maxStamina = Stats->GetStatValue("MaxSTA");
			if (stamina >= maxStamina) {
				stamina = maxStamina;
			}

			UpdateStaminaUI(stamina);
			// Reset the stamina
			Stats->SetStatValue("STA", stamina);
		}
	}
}

void ARPGCharacter::UpdateStaminaUI(int stamina, int maxStamina) {
	
	if (!RPGHUD) { return; }

	UStaminaWidget* staminaBar = RPGHUD->StaminaBarWidget;
	if (!staminaBar) { return; }

	staminaBar->SetStamina(stamina);

	if (maxStamina != 0) {
		staminaBar->SetMaxStamina(maxStamina);
	}
	// The stamina bar is resized acording to the ratio of the stamina and its maximum value
	staminaBar->ResizeStaminaBar((float)stamina / Stats->GetStatValue("MAX_STA"));

}

void ARPGCharacter::ClearTimer() {
	GetWorldTimerManager().ClearTimer(RegenerateStaminaTimerHandle);
}

void ARPGCharacter::RestartTimer() {
	GetWorld()->GetTimerManager().SetTimer(RegenerateStaminaTimerHandle, this, &ARPGCharacter::RegenerateStamina, 0.5f, true);
	// basically Invoke, calls the method RegenerateStamina after 0.5 seconds
}

void ARPGCharacter::OnLockBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){


	IHealth* health = Cast<IHealth>(OtherActor);

	if (health && !health->IsDead()) {
		// Try getting the ILock interface
		ILock* targetLock = Cast<ILock>(OtherActor);

		// if the target implements the ILock
		if (targetLock) {
			targetLock->ShowLocked(true);
			// Set the current target
			currentTarget = OtherActor;
		}
	}
}

void ARPGCharacter::OnLockBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	ILock* targetLock = Cast<ILock>(OtherActor);

	if (targetLock) {
		// Hide the widget
		targetLock->ShowLocked(false);
		// Reset the target
		currentTarget = NULL;
	}
}