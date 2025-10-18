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
	
}

// Called every frame
void AMJ_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMJ_PlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMJ_PlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMJ_PlayerCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void AMJ_PlayerCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

// Called to bind functionality to input
void AMJ_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Walking
	PlayerInputComponent->BindAxis("MoveForward", this, &AMJ_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMJ_PlayerCharacter::MoveRight);

	// Looking
	PlayerInputComponent->BindAxis("TurnYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnPitch", this, &APawn::AddControllerPitchInput);

	// Jumping
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMJ_PlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMJ_PlayerCharacter::StopSprinting);
}

