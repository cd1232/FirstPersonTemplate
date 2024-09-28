// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIHelpers.generated.h"

class UPlayerHUDWidget;

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UUIHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static bool ProjectWorldToScreenConstrained(UWorld* World, FVector WorldPosition, FVector2D WidgetDesiredSize, FVector2D& OutScreenPosition);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UPlayerHUDWidget* GetPlayerHUD(UObject* WorldContextObject);
};
