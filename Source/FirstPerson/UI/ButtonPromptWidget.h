// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonPromptWidget.generated.h"

class UImage;
class UCommonTextBlock;

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UButtonPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetPrompt(FKey Key, FText PromptText);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UImage* Image_Button;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* Text_Prompt;
};
