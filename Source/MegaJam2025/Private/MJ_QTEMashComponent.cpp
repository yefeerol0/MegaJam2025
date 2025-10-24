// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "MJ_QTEMashComponent.h"

// Sets default values for this component's properties
UMJ_QTEMashComponent::UMJ_QTEMashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false; // Baþlangýçta Tick kapalý
	bIsQTEActive = false;
	ProgressPerMash = 0.1f;
	ProgressDecayRate = 0.05f;
	QTELengthSeconds = 0.0f; // Zaman aþýmý yok
	CurrentProgress = 0.0f;

}


void UMJ_QTEMashComponent::StartQTE(APlayerController* Player)
{
	if (!Player) return;

	OwningPlayer = Player;
	CurrentProgress = 0.0f;
	CurrentQTEZamani = 0.0f;
	bIsQTEActive = true;

	SetComponentTickEnabled(true);

	if (!QTEInputComponent)
	{
		QTEInputComponent = NewObject<UInputComponent>(this);
		QTEInputComponent->RegisterComponent();
	}

	QTEInputComponent->BindAction("QTE_Mash", IE_Pressed, this, &UMJ_QTEMashComponent::OnMashInput);

	OwningPlayer->PushInputComponent(QTEInputComponent);

	if (OwningPlayer->GetPawn())
	{
		OwningPlayer->GetPawn()->DisableInput(OwningPlayer);
	}
}

void UMJ_QTEMashComponent::StopQTE(bool bWasSuccessful)
{
	if (!bIsQTEActive) return;

	bIsQTEActive = false;
	SetComponentTickEnabled(false);

	if (OwningPlayer && QTEInputComponent)
	{
		OwningPlayer->PopInputComponent(QTEInputComponent);
	}

	if (OwningPlayer->GetPawn())
	{
		OwningPlayer->GetPawn()->EnableInput(OwningPlayer);
	}

	OwningPlayer = nullptr;

	if (bWasSuccessful)
	{
		OnQTESuccess.Broadcast();
	}
	else
	{
		OnQTEFail.Broadcast();
	}
}

void UMJ_QTEMashComponent::OnMashInput()
{
	if (!bIsQTEActive) return;

	CurrentProgress += ProgressPerMash;
	UGameplayStatics::PlaySound2D(GetWorld(), QTESuccess, 0.5, 1.4, 0, NULL);
	CurrentProgress = FMath::Clamp(CurrentProgress, 0.0f, 1.0f);

	if (CurrentProgress >= 1.0f)
	{
		StopQTE(true);
	}
}

// Called when the game starts
void UMJ_QTEMashComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UMJ_QTEMashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsQTEActive) return;

	CurrentProgress -= ProgressDecayRate * DeltaTime;
	CurrentProgress = FMath::Clamp(CurrentProgress, 0.0f, 1.0f);

	if (QTELengthSeconds > 0.0f)
	{
		CurrentQTEZamani += DeltaTime;
		if (CurrentQTEZamani >= QTELengthSeconds)
		{
			StopQTE(false);
		}
	}
}



