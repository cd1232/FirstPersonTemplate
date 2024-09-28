// Fill out your copyright notice in the Description page of Project Settings.


#include "PointOfInterestComponent.h"
#include "FirstPersonPlayerController.h"
#include "UI/PointOfInterestWidget.h"
#include "UI/POIDataAsset.h"

// Sets default values for this component's properties
UPointOfInterestComponent::UPointOfInterestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPointOfInterestComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPointOfInterestComponent::EnterState(EPOIState NewState)
{
	CurrentState = NewState;
	if (NewState != EPOIState::Hidden)
	{
		if (!POIWidget.IsValid())
		{
			// Create one
			if (AFirstPersonPlayerController* FPPController = GetWorld()->GetFirstPlayerController<AFirstPersonPlayerController>())
			{
				POIWidget = FPPController->AddPOI(this);
				check(POIWidget.IsValid());
			}
		}
	}

	POIWidget.Get()->EnterState(NewState);
	PreviousState = CurrentState;
}

EPOIState UPointOfInterestComponent::GetCurrentState() const
{
	return CurrentState;
}

TSubclassOf<UPointOfInterestWidget> UPointOfInterestComponent::GetPOIWidgetClass() const
{
	return POIData->POIWidgetClass;
}

UPOIDataAsset* UPointOfInterestComponent::GetPOIData() const
{
	return POIData;
}

