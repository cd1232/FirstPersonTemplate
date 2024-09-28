// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UI/POIState.h"
#include "PointOfInterestComponent.generated.h"

class UPointOfInterestWidget;
class UPOIDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSON_API UPointOfInterestComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPointOfInterestComponent();

	void EnterState(EPOIState NewState);

	EPOIState GetCurrentState() const;

	TSubclassOf<UPointOfInterestWidget> GetPOIWidgetClass() const;

	UPOIDataAsset* GetPOIData() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	TWeakObjectPtr<UPointOfInterestWidget> POIWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPOIDataAsset* POIData;
	
	EPOIState PreviousState = EPOIState::Hidden;
	EPOIState CurrentState = EPOIState::Hidden;		
};
