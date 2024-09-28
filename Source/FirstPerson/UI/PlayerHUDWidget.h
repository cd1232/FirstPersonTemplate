// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UCanvasPanel;
class UHorizontalBox;
class UButtonPromptWidget;

/**
 * 
 */
UCLASS()
class FIRSTPERSON_API UPlayerHUDWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	int32 AddButtonPrompt(FKey Key, FText PromptText);
	void RemoveButtonPrompt(int32 ButtonID);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* CanvasHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UHorizontalBox* HB_ButtonPrompts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UButtonPromptWidget> ButtonPromptClass;

	UPROPERTY()
	TMap<int32, UButtonPromptWidget*> ButtonPromptMap;

	int32 ButtonID = 0;
};
