// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"

class UInputMappingContext;
class UPointOfInterestComponent;
class UPointOfInterestWidget;
class UPlayerHUDWidget;

/**
 *
 */
UCLASS()
class FIRSTPERSON_API AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	UPointOfInterestWidget* AddPOI(UPointOfInterestComponent* Component);

	UPlayerHUDWidget* GetPlayerHUD() const;

protected:
	virtual void BeginPlay() override;
	
protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPlayerHUDWidget* PlayerHUD;
};
