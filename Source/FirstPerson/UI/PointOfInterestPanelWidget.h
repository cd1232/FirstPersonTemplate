// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UObject/ObjectKey.h"

#include "PointOfInterestPanelWidget.generated.h"

class UPointOfInterestWidget;
class UCanvasPanel;
class UCanvasPanelSlot;
class UOverlay;
class UPointOfInterestComponent;

USTRUCT()
struct FPOIEntry
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UPointOfInterestComponent> Component = nullptr;

	UPROPERTY()
	UPointOfInterestWidget* Widget = nullptr;

	UPROPERTY()
	UCanvasPanelSlot* Slot = nullptr;

	UPROPERTY()
	UOverlay* ContainerWidget = nullptr;
};

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UPointOfInterestPanelWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UPointOfInterestWidget* AddPOI(UPointOfInterestComponent* POIComponent);
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> POIContainer;

	TMap<FObjectKey, FPOIEntry> ComponentMap;
};
