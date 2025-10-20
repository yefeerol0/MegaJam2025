// Fill out your copyright notice in the Description page of Project Settings.

#include "MJ_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMJ_PlayerCharacter::AMJ_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AMJ_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	TargetFOV = WalkFOV;
	CameraComp->SetFieldOfView(WalkFOV);

	IsScriptOpen = true;
}

void AMJ_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraComp->FieldOfView = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, 5.0f);
}
void AMJ_PlayerCharacter::MoveForward(float Value)
{
	if (!IsScriptOpen)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMJ_PlayerCharacter::MoveRight(float Value)
{
	if (!IsScriptOpen)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMJ_PlayerCharacter::LookVertical(float Value)
{
	if (!IsScriptOpen)
	{
		AddControllerPitchInput(Value);
	}
}

void AMJ_PlayerCharacter::LookHorizontal(float Value)
{
	if (!IsScriptOpen)
	{
		AddControllerYawInput(Value);
	}
}

void AMJ_PlayerCharacter::Sprint()
{
	if (!IsScriptOpen)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
		TargetFOV = SprintFOV;
	}
}

void AMJ_PlayerCharacter::StopSprinting()
{
	if (!IsScriptOpen)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		TargetFOV = WalkFOV;
	}
}

void AMJ_PlayerCharacter::CharacterJump()
{
	if (!IsScriptOpen)
	{
		Jump();
	}
}

// Called to bind functionality to input
void AMJ_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Walking
	PlayerInputComponent->BindAxis("MoveForward", this, &AMJ_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMJ_PlayerCharacter::MoveRight);

	// Looking
	PlayerInputComponent->BindAxis("TurnYaw", this, &AMJ_PlayerCharacter::LookHorizontal);
	PlayerInputComponent->BindAxis("TurnPitch", this, &AMJ_PlayerCharacter::LookVertical);

	// Jumping
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMJ_PlayerCharacter::CharacterJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMJ_PlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMJ_PlayerCharacter::StopSprinting);

	// Turning off Script Menu
	PlayerInputComponent->BindAction("TurnOffScript", IE_Pressed, this, &AMJ_PlayerCharacter::TurnOffScript);
}