// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJ_QTEMashComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQTESuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQTEFail);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGAJAM2025_API UMJ_QTEMashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMJ_QTEMashComponent();

	UPROPERTY(BlueprintAssignable, Category = "QTE")
	FOnQTESuccess OnQTESuccess;

	UPROPERTY(BlueprintAssignable, Category = "QTE")
	FOnQTEFail OnQTEFail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QTE Settings")
	float ProgressPerMash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QTE Settings")
	float ProgressDecayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QTE Settings")
	float QTELengthSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QTE State")
	float CurrentProgress;

	UFUNCTION(BlueprintCallable, Category = "QTE")
	void StartQTE(APlayerController* Player);

	UFUNCTION(BlueprintCallable, Category = "QTE")
	void StopQTE(bool bWasSuccessful);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void OnMashInput();

	bool bIsQTEActive;
	float CurrentQTEZamani;

	UPROPERTY()
	APlayerController* OwningPlayer;

	UPROPERTY()
	UInputComponent* QTEInputComponent;
		
};
