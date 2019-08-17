// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorPalatteSaturateAndValueDragArea.h"

UColorPalatteSaturateAndValueDragArea::UColorPalatteSaturateAndValueDragArea()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UColorPalatteSaturateAndValueDragArea::BeginPlay()
{
	Super::BeginPlay();
}
void UColorPalatteSaturateAndValueDragArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UColorPalatteSaturateAndValueDragArea::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
}

bool UColorPalatteSaturateAndValueDragArea::OnPointerBeginDrag_Implementation(const FLGUIPointerEventData& eventData)
{
	return true;
}
bool UColorPalatteSaturateAndValueDragArea::OnPointerDrag_Implementation(const FLGUIPointerEventData& eventData)
{
	if (_RootUIItem == nullptr)
	{
		_RootUIItem = (UUIItem*)(GetOwner()->GetRootComponent());
	}
	auto worldPoint = eventData.GetWorldPointInPlane();
	FVector2D newLocation = FVector2D(eventData.pressWorldToLocalTransform.TransformPosition(worldPoint));
	newLocation.X = FMath::Clamp(newLocation.X, 0.0f, _RootUIItem->GetWidth());
	newLocation.Y = FMath::Clamp(newLocation.Y, 0.0f, _RootUIItem->GetHeight());
	if (SaturateAndValueChangeDelegate.IsBound())
		SaturateAndValueChangeDelegate.Execute(FVector2D(newLocation.X / _RootUIItem->GetWidth(), newLocation.Y / _RootUIItem->GetHeight()));
	_PickerCircleActor->GetUISprite()->SetAnchorOffset(newLocation);
	return true;
}
bool UColorPalatteSaturateAndValueDragArea::OnPointerEndDrag_Implementation(const FLGUIPointerEventData& eventData)
{
	return true;
}

bool UColorPalatteSaturateAndValueDragArea::OnPointerDown_Implementation(const FLGUIPointerEventData& eventData)
{
	OnPointerDrag_Implementation(eventData);
	return true;
}
bool UColorPalatteSaturateAndValueDragArea::OnPointerUp_Implementation(const FLGUIPointerEventData& eventData)
{
	return true;
}

void UColorPalatteSaturateAndValueDragArea::SetSaturateAndValue(float InSaturate, float InValue)
{
	if (_RootUIItem == nullptr)
	{
		_RootUIItem = (UUIItem*)(GetOwner()->GetRootComponent());
	}
	FVector2D newLocation(InSaturate * _RootUIItem->GetWidth(), InValue * _RootUIItem->GetHeight());
	_PickerCircleActor->GetUISprite()->SetAnchorOffset(newLocation);
}
