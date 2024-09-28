// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPerson/UI/PointOfInterestWidget.h"
#include "FirstPerson/PointOfInterestComponent.h"

void UPointOfInterestWidget::AddPOIComponent(UPointOfInterestComponent* NewPOIComponent)
{
	POIComponent = NewPOIComponent;
}

UPointOfInterestComponent* UPointOfInterestWidget::GetPOIComponent()
{
	return POIComponent.Get();
}

EPOIState UPointOfInterestWidget::GetCurrentState() const
{
	return CurrentState;
}

void UPointOfInterestWidget::EnterState(EPOIState NewState)
{
	CurrentState = NewState;
	EnterState_BP(NewState, PreviousState);
	PreviousState = NewState;
}
