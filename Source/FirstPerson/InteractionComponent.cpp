// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "FirstPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/OverlapResult.h"
#include "IInteractable.h"
#include "UI/POIDataAsset.h"
#include "PointOfInterestComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::StartInteraction()
{
	if (CurrentInteractableActor.IsValid() && !bIsInInteraction)
	{
		bIsInInteraction = true;
		if (CurrentInteractableActor.Get()->Implements<UInteractable>())
		{
			IInteractable* Interactable = Cast<IInteractable>(CurrentInteractableActor.Get());
			if (Interactable)
			{
				Interactable->StartInteraction();
				FInteractableDelegate& OnInteractionFinished = Interactable->GetInteractionFinishedDelegate();
				OnInteractionFinished.AddDynamic(this, &ThisClass::OnInteractionFinished);
			}

		}
	}
}

void UInteractionComponent::CancelInteraction()
{
	if (CurrentInteractableActor.IsValid() && bIsInInteraction)
	{
		bIsInInteraction = false;
		if (CurrentInteractableActor.Get()->Implements<UInteractable>())
		{
			IInteractable* Interactable = Cast<IInteractable>(CurrentInteractableActor.Get());
			if (Interactable)
			{
				Interactable->CancelInteraction();

				FInteractableDelegate& OnInteractionFinished = Interactable->GetInteractionFinishedDelegate();
				OnInteractionFinished.RemoveDynamic(this, &ThisClass::OnInteractionFinished);
			}
		}
	}
}

bool UInteractionComponent::IsInteracting() const
{
	return bIsInInteraction;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the parent actors camera
	ParentCameraComponent = Cast<AFirstPersonCharacter>(GetOwner())->GetFirstPersonCameraComponent();
	check(ParentCameraComponent.IsValid());

	PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());

	OverlapDelegate.BindUObject(this, &UInteractionComponent::OnTraceCompleted);
	GetWorld()->GetTimerManager().SetTimer(QueryTimerHandle, this, &ThisClass::QueryInteractions, InteractionTickRate, true);
}

void UInteractionComponent::OnInteractionFinished()
{
	CancelInteraction();
}

void UInteractionComponent::QueryInteractions()
{
	if (bIsInInteraction)
		return;

	FVector StartLocation = ParentCameraComponent.Get()->GetComponentLocation();
	FVector EndLocation = StartLocation + ParentCameraComponent.Get()->GetForwardVector() * InteractionTraceDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	TraceHandle = GetWorld()->AsyncOverlapByChannel(StartLocation, FQuat::Identity, UEngineTypes::ConvertToCollisionChannel(TraceType),
		FCollisionShape::MakeSphere(InteractionTraceDistance), QueryParams, FCollisionResponseParams::DefaultResponseParam, &OverlapDelegate);
}

void UInteractionComponent::OnTraceCompleted(const FTraceHandle& InTraceHandle, FOverlapDatum& OverlapData)
{
	AActor* BestInteractableActor = nullptr;
	CurrentInteractableActor.Reset();
	float BestDotProduct = 0.0f;

	TArray<TWeakObjectPtr<AActor>> InteractableActorsInRangeThisQuery;
	if (OverlapData.OutOverlaps.Num() > 0)
	{
		InteractableActorsInRangeThisQuery.Reserve(OverlapData.OutOverlaps.Num());
		for (const FOverlapResult& Overlap : OverlapData.OutOverlaps)
		{
			AActor* OverlappedActor = Overlap.GetActor();
			if (OverlappedActor->Implements<UInteractable>())
			{
				const bool IsInteractable = IInteractable::Execute_IsInteractable(OverlappedActor);
				if (!IsInteractable)
					continue;

				InteractableActorsInRangeThisQuery.AddUnique(OverlappedActor);

				FVector ViewStart;
				FRotator ViewRot;
				PlayerController->GetPlayerViewPoint(ViewStart, ViewRot);
				
				FVector CameraToActor = OverlappedActor->GetActorLocation() - ViewStart;
				CameraToActor.Normalize();

				const FVector ViewDir = ViewRot.Vector();
				const float dotProduct = FVector::DotProduct(CameraToActor, ViewDir);
			
				if (dotProduct > BestDotProduct)
				{
					// new best dot product
					BestInteractableActor = OverlappedActor;
					BestDotProduct = dotProduct;
				}
			}
		}	
	}

	for (TWeakObjectPtr<AActor> InteractableActor : InteractableActorsInRangeThisQuery)
	{
		// Have to go through a separate time so that we have the best interactable actor and can separate that from entering the visible state again 
		UPointOfInterestComponent* poiComponent = Cast<UPointOfInterestComponent>(IInteractable::Execute_GetLinkedPointOfInterestComponent(InteractableActor.Get()));
		
		if (poiComponent)
		{
			poiComponent->EnterState(EPOIState::Visible);
		}
	}

	for (TWeakObjectPtr<AActor> InteractableActor : InteractableActorsInRangeLastQuery)
	{
		if (InteractableActor.IsValid())
		{
			// If it was in range last query but isn't in this query it means it's out of range now
			if (!InteractableActorsInRangeThisQuery.Contains(InteractableActor))
			{
				UPointOfInterestComponent* poiComponent = Cast<UPointOfInterestComponent>(IInteractable::Execute_GetLinkedPointOfInterestComponent(InteractableActor.Get()));
				if (poiComponent)
				{
					poiComponent->EnterState(EPOIState::Hidden);
				}
			}
		}
	}

	// close enough
	if (BestInteractableActor && BestDotProduct > 0.75f)
	{
		UPointOfInterestComponent* poiComponent = Cast<UPointOfInterestComponent>(IInteractable::Execute_GetLinkedPointOfInterestComponent(BestInteractableActor));
		if (poiComponent)
		{
			float distance = FVector::Dist(ParentCameraComponent->GetComponentLocation(), poiComponent->GetComponentLocation());
			if (distance <= poiComponent->GetPOIData()->InteractionDistance)
			{
				// We have one we can now interact
				CurrentInteractableActor = BestInteractableActor;
				poiComponent->EnterState(EPOIState::Active);
			}
		}
	}

	InteractableActorsInRangeLastQuery = InteractableActorsInRangeThisQuery;
}

