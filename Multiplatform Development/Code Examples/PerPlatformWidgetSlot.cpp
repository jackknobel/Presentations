// Fill out your copyright notice in the Description page of Project Settings.


#include "PerPlatformWidgetSlot.h"

// UE Includes
#if WITH_EDITOR
	#include "PlatformInfo.h"
	#include "ITargetPlatform.h"
	#include "ITargetPlatformManagerModule.h"
#endif

UPerPlatformWidgetSlot::UPerPlatformWidgetSlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Enabled(true)
{}

#if WITH_EDITOR
void UPerPlatformWidgetSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	/*	
		We need to hide this is in PIE/Standalone manually because it doesn't use cooked content 
		(so it doesn't invoke the `NeedsLoadForTargetPlatform` function)
	*/
	const UWorld* World = GetWorld();
	if (!IsTemplate() 
		&& World != nullptr 
		&& (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE))
	{
		ITargetPlatform* CurrentPlatform = GetTargetPlatformManagerRef().GetRunningTargetPlatform();
		if (!Enabled.GetValueForPlatformIdentifiers(CurrentPlatform->GetPlatformInfo().PlatformGroupName))
		{
			this->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

bool UPerPlatformWidgetSlot::NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const
{
	if (TargetPlatform != nullptr)
	{
		return Enabled.GetValueForPlatformIdentifiers(TargetPlatform->GetPlatformInfo().PlatformGroupName);
	}

	return Enabled.Default;
}
#endif