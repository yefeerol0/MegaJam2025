// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MJ_QTE_SkillCheckComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillCheckInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChallengeComplete);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGAJAM2025_API UMJ_QTE_SkillCheckComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMJ_QTE_SkillCheckComponent();

	UPROPERTY(BlueprintAssignable, Category = "SkillCheck")
	FOnSkillCheckInput OnSkillCheckInputPressed;

	UPROPERTY(BlueprintAssignable, Category = "SkillCheck")
	FOnChallengeComplete OnChallengeComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillCheck Settings")
	int SuccessesRequired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillCheck State")
	int CurrentSuccessCount;

	UFUNCTION(BlueprintCallable, Category = "SkillCheck")
	void StartChallenge(APlayerController* Player);

	UFUNCTION(BlueprintCallable, Category = "SkillCheck")
	void StopChallenge();

	UFUNCTION(BlueprintCallable, Category = "SkillCheck")
	void ReportSkillCheckResult(bool bWasSuccess);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnInputPressed();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	APlayerController* OwningPlayer;

	UPROPERTY()
	UInputComponent* SkillCheckInputComponent;

		
};
