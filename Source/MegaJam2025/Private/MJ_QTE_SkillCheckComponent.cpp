// Fill out your copyright notice in the Description page of Project Settings.


#include "MJ_QTE_SkillCheckComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UMJ_QTE_SkillCheckComponent::UMJ_QTE_SkillCheckComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SuccessesRequired = 3;
	CurrentSuccessCount = 0;
}


void UMJ_QTE_SkillCheckComponent::StartChallenge(APlayerController* Player)
{
	if (!Player) return;

	OwningPlayer = Player;
	CurrentSuccessCount = 0;

	if (!SkillCheckInputComponent)
	{
		SkillCheckInputComponent = NewObject<UInputComponent>(this);
		SkillCheckInputComponent->RegisterComponent();
	}

	SkillCheckInputComponent->BindAction("QTE_Mash", IE_Pressed, this, &UMJ_QTE_SkillCheckComponent::OnInputPressed);

	OwningPlayer->PushInputComponent(SkillCheckInputComponent);
}

void UMJ_QTE_SkillCheckComponent::StopChallenge()
{
	if (OwningPlayer && SkillCheckInputComponent)
	{
		OwningPlayer->PopInputComponent(SkillCheckInputComponent);
	}
	OwningPlayer = nullptr;
}

void UMJ_QTE_SkillCheckComponent::OnInputPressed()
{
	OnSkillCheckInputPressed.Broadcast();
}

void UMJ_QTE_SkillCheckComponent::ReportSkillCheckResult(bool bWasSuccess)
{
	if (bWasSuccess)
	{
		CurrentSuccessCount++;
		if (CurrentSuccessCount >= SuccessesRequired)
		{
			OnChallengeComplete.Broadcast();
			StopChallenge();
		}
	}
	else
	{
		CurrentSuccessCount = 0;
	}
}



// Called when the game starts
void UMJ_QTE_SkillCheckComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




// Called every frame
void UMJ_QTE_SkillCheckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

