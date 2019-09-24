// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/NamedSlot.h"
#include "PerPlatformWidgetSlot.generated.h"

/**
 * 
 */
UCLASS()
class UPerPlatformWidgetSlot : public UNamedSlot
{
	GENERATED_BODY()

	UPerPlatformWidgetSlot(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = Widget)
	FPerPlatformBool Enabled;

#if WITH_EDITOR
	void SynchronizeProperties() override final;

	bool NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const override final;
#endif
};
