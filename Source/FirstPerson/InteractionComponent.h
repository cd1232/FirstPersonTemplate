// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class UCameraComponent;
class APlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSON_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	void StartInteraction();
	void CancelInteraction();

	bool IsInteracting() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnInteractionFinished();

protected:
	UFUNCTION()
	void QueryInteractions();

	void OnTraceCompleted(const FTraceHandle& InTraceHandle, FOverlapDatum& OverlapData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InteractionTraceDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InteractionTickRate = 0.1f;


private:
	TWeakObjectPtr<AActor> CurrentInteractableActor;

	TArray<TWeakObjectPtr<AActor>> InteractableActorsInRangeLastQuery;

	FTraceHandle TraceHandle;
	FOverlapDelegate OverlapDelegate;

	FTimerHandle QueryTimerHandle;

	TWeakObjectPtr<UCameraComponent> ParentCameraComponent;
	TWeakObjectPtr<APlayerController> PlayerController;

	bool bIsInInteraction = false;
};
