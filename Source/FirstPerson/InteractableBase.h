// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"

#include "InteractableBase.generated.h"

class UInputMappingContext;

UCLASS()
class FIRSTPERSON_API AInteractableBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	virtual void BeginPlay() override;

	virtual FInteractableDelegate& GetInteractionFinishedDelegate() { return OnInteractionFinished; };

	virtual bool IsInteractable_Implementation() override;

	virtual void StartInteraction() override;
	virtual void CancelInteraction() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartInteraction_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void CancelInteraction_BP();

protected:
	UFUNCTION()
	void ShowButtonPrompts();

protected:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadOnly)
	FInteractableDelegate OnInteractionFinished;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* InteractionMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsInteractable = true;

	FTimerHandle ShowButtonPromptsTimerHandle;

	UPROPERTY()
	TArray<int32> CreatedButtonIDs;
};
