// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LockpickDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FLockpickPinData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, ClampMax = 7))
	int PinPosition = 5;
};

/**
 * 
 */
UCLASS(BlueprintType)
class FIRSTPERSON_API ULockpickDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FLockpickPinData> Pins;
	
};
