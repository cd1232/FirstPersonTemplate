// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "ButtonPromptWidget.h"

int32 UPlayerHUDWidget::AddButtonPrompt(FKey Key, FText PromptText)
{
	UButtonPromptWidget* ButtonPromptWidget = CreateWidget<UButtonPromptWidget>(GetOwningPlayer(), ButtonPromptClass);
	ButtonPromptWidget->SetPrompt(Key, PromptText);

	ButtonPromptMap.Add(ButtonID, ButtonPromptWidget);
	const int32 NewButtonID = ButtonID;
	++ButtonID;

	UHorizontalBoxSlot* HBBoxSlot = HB_ButtonPrompts->AddChildToHorizontalBox(ButtonPromptWidget);
	HBBoxSlot->SetPadding(FMargin(30.0f, 0.0f, 0.0f, 0.0f));

	return NewButtonID;
}

void UPlayerHUDWidget::RemoveButtonPrompt(int32 InButtonID)
{
	UButtonPromptWidget* WidgetToRemove = ButtonPromptMap.FindAndRemoveChecked(InButtonID);
	if (WidgetToRemove)
	{
		WidgetToRemove->RemoveFromParent();
	}
}
