// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ButtonPromptWidget.h"

#include "CommonTextBlock.h"
#include "CommonInputSubsystem.h"
#include "CommonUITypes.h"
#include "Components/Image.h"
#include "CommonInputBaseTypes.h"

void UButtonPromptWidget::SetPrompt(FKey Key, FText PromptText)
{
	Text_Prompt->SetText(PromptText);

	if (const UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetOwningPlayer()->GetLocalPlayer()))
	{
		FSlateBrush IconBrush;
		UCommonInputPlatformSettings::Get()->TryGetInputBrush(IconBrush, Key, CommonInputSubsystem->GetCurrentInputType(), CommonInputSubsystem->GetCurrentGamepadName());
		Image_Button->SetBrush(IconBrush);
	}
}
