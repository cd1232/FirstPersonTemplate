// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerMappableKeySettings.h"

#include "UI/PlayerHUDWidget.h"
#include "UI/UIHelpers.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	CreateInputComponent(UEnhancedInputComponent::StaticClass());
}

void AInteractableBase::StartInteraction()
{
	if (IInteractable::Execute_IsInteractable(this))
	{
		UEnhancedInputWorldSubsystem* InputWorldSubsystem = GetWorld()->GetSubsystem<UEnhancedInputWorldSubsystem>();
		InputWorldSubsystem->AddActorInputComponent(this);
		InputWorldSubsystem->AddMappingContext(InteractionMappingContext, 1);

		GetWorld()->GetTimerManager().SetTimer(ShowButtonPromptsTimerHandle, this, &ThisClass::ShowButtonPrompts, 0.025f, false);

		StartInteraction_BP();
	}
}

void AInteractableBase::CancelInteraction()
{
	UEnhancedInputWorldSubsystem* InputWorldSubsystem = GetWorld()->GetSubsystem<UEnhancedInputWorldSubsystem>();
	InputWorldSubsystem->RemoveActorInputComponent(this);
	InputWorldSubsystem->RemoveMappingContext(InteractionMappingContext);

	if (UPlayerHUDWidget* PlayerHUD = UUIHelpers::GetPlayerHUD(GetWorld()))
	{	
		for (int32 ButtonID : CreatedButtonIDs)
		{
			PlayerHUD->RemoveButtonPrompt(ButtonID);
		}
	}
	CreatedButtonIDs.Empty();

	CancelInteraction_BP();
}

void AInteractableBase::ShowButtonPrompts()
{
	if (UPlayerHUDWidget* PlayerHUD = UUIHelpers::GetPlayerHUD(GetWorld()))
	{
		UEnhancedInputComponent* EnhancedInputComponent = FindComponentByClass<UEnhancedInputComponent>();
		const TArray<TUniquePtr<FEnhancedInputActionEventBinding>>& EventBindings = EnhancedInputComponent->GetActionEventBindings();

		UEnhancedInputWorldSubsystem* InputWorldSubsystem = GetWorld()->GetSubsystem<UEnhancedInputWorldSubsystem>();
		for (const TUniquePtr<FEnhancedInputActionEventBinding>& Binding : EventBindings)
		{
			const UInputAction* Action = Binding->GetAction();
			TArray<FKey> MappedKeys = InputWorldSubsystem->QueryKeysMappedToAction(Action);
			UPlayerMappableKeySettings* KeySettings = Action->GetPlayerMappableKeySettings();
			if (MappedKeys.Num() > 0)
			{
				// Just getting the first key for now
				// Could add more functionality from CommonUI to get first key of a certain input type
				int32 ButtonID = PlayerHUD->AddButtonPrompt(MappedKeys[0], KeySettings->DisplayName);
				CreatedButtonIDs.Add(ButtonID);
			}
		}
	}	
}

bool AInteractableBase::IsInteractable_Implementation()
{
	return bIsInteractable;
}

