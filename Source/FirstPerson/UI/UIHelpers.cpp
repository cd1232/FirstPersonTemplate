// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIHelpers.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/PlayerController.h"

#include "FirstPersonPlayerController.h"


bool UUIHelpers::ProjectWorldToScreenConstrained(UWorld* World, FVector WorldPosition, FVector2D WidgetDesiredSize, FVector2D& OutScreenPosition)
{
	FVector2D screenLocation;
	APlayerController* playerController = World->GetFirstPlayerController();

	bool bProjected = UGameplayStatics::ProjectWorldToScreen(playerController, WorldPosition, screenLocation, true);
	const FVector2D roundedPosition2D(FMath::RoundToInt(screenLocation.X), FMath::RoundToInt(screenLocation.Y));

	FVector2D viewportPosition;
	USlateBlueprintLibrary::ScreenToViewport(playerController, roundedPosition2D, viewportPosition);

	// Clamp to the edges of the screen
	int32 viewportSizeX, viewportSizeY;
	playerController->GetViewportSize(viewportSizeX, viewportSizeY);
	const float viewportScale = UWidgetLayoutLibrary::GetViewportScale(World);

	float constrainedViewportSizeX = 0.0f;
	float constrainedViewportSizeY = 0.0f;

	// Get aspect ratio from player controller
	const float aspectRatio = 1.777778f;

	float currentAspectRatio = (float)viewportSizeX / (float)viewportSizeY;

	if (currentAspectRatio > aspectRatio)
	{
		constrainedViewportSizeX = viewportSizeY * aspectRatio;
		constrainedViewportSizeY = viewportSizeY;
	}
	else
	{
		constrainedViewportSizeX = viewportSizeX;
		constrainedViewportSizeY = viewportSizeX / aspectRatio;
	}

	//const float minViewportX = WidgetDesiredSize.X / 2 + (viewportSizeX - constrainedViewportSizeX);
	//const float minViewportY = WidgetDesiredSize.Y / 2 + (viewportSizeY - constrainedViewportSizeY);
	const float maxViewportX = constrainedViewportSizeX / viewportScale - (WidgetDesiredSize.X / 2);
	const float maxViewportY = constrainedViewportSizeY / viewportScale - (WidgetDesiredSize.Y / 2);

	if (viewportPosition.X <  WidgetDesiredSize.X / 2 || viewportPosition.X > maxViewportX ||
		viewportPosition.Y < WidgetDesiredSize.Y / 2 || viewportPosition.Y > maxViewportY)
	{
		// Not technically projected since it is past the player viewport constraint
		// It will still clamp after this
		bProjected = false;
	}

	// Viewport Position does not take into account the viewport scale. so it is a max of 1920x1080
	// Viewport Size is the actual size of the viewport (so if it was full screen on a 1440p monitor it would be 2560x1440 and a 1080p monitor would be 1920x1080
	viewportPosition.X = FMath::Clamp(viewportPosition.X, WidgetDesiredSize.X / 2, maxViewportX);
	viewportPosition.Y = FMath::Clamp(viewportPosition.Y, WidgetDesiredSize.Y / 2, maxViewportY);

	OutScreenPosition = viewportPosition;

	return bProjected;
}

UPlayerHUDWidget* UUIHelpers::GetPlayerHUD(UObject* WorldContextObject)
{	
	return Cast<AFirstPersonPlayerController>(WorldContextObject->GetWorld()->GetFirstPlayerController())->GetPlayerHUD();
}
