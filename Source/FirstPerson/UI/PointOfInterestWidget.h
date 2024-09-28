// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "POIState.h"
#include "PointOfInterestWidget.generated.h"

class UPointOfInterestComponent;

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UPointOfInterestWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPOIComponent(UPointOfInterestComponent* NewPOIComponent);

	UPointOfInterestComponent* GetPOIComponent();
	EPOIState GetCurrentState() const;

	void EnterState(EPOIState NewState);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void EnterState_BP(EPOIState NewState, EPOIState OldPreviousState);

private:
	EPOIState CurrentState = EPOIState::Hidden;
	EPOIState PreviousState = EPOIState::Hidden;
	
	TWeakObjectPtr<UPointOfInterestComponent> POIComponent;
};
