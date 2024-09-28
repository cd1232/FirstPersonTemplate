// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "POIDataAsset.generated.h"

class UPointOfInterestWidget;

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UPOIDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPointOfInterestWidget> POIWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float VisibleDistance = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionDistance = 150.0f;
};
