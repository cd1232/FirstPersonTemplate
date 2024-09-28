// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PointOfInterestPanelWidget.h"

#include "UIHelpers.h"
#include "PointOfInterestWidget.h"
#include "PointOfInterestComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Engine/GameViewportClient.h"
#include "Slate/SGameLayerManager.h"
#include "POIState.h"
#include "Components/Overlay.h"
#include "Blueprint/WidgetTree.h"

UPointOfInterestWidget* UPointOfInterestPanelWidget::AddPOI(UPointOfInterestComponent* POIComponent)
{
	if (POIComponent)
	{
		FPOIEntry& Entry = ComponentMap.FindOrAdd(FObjectKey(POIComponent));
		Entry.Component = POIComponent;
		Entry.Widget = CreateWidget<UPointOfInterestWidget>(GetOwningPlayer(), POIComponent->GetPOIWidgetClass());
		Entry.ContainerWidget = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass());		
		
		Entry.ContainerWidget->AddChildToOverlay(Entry.Widget);
		Entry.Slot = POIContainer->AddChildToCanvas(Entry.ContainerWidget);

		return Entry.Widget;
	}

	return nullptr;
}

void UPointOfInterestPanelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (auto It = ComponentMap.CreateIterator(); It; ++It)
	{
		FPOIEntry& Entry = It.Value();

		if (UPointOfInterestComponent* POIComponent = Entry.Component.Get())
		{
			FVector2D OutScreenPosition;
			const bool bIsConstrained = UUIHelpers::ProjectWorldToScreenConstrained(GetWorld(), POIComponent->GetComponentLocation(),
				Entry.Widget->GetDesiredSize(), OutScreenPosition);

			if (bIsConstrained)
			{
				UCanvasPanelSlot* CanvasSlot = Entry.Slot;
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasSlot->SetAnchors(FAnchors(0, 0, 0, 0));
				CanvasSlot->SetAutoSize(true);
				CanvasSlot->SetPosition(OutScreenPosition);
				Entry.ContainerWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
			else
			{
				Entry.ContainerWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}
