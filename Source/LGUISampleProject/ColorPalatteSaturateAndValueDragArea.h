// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LGUIHeaders.h"
#include "ColorPalatteSaturateAndValueDragArea.generated.h"


//HSV颜色中的S和V拖拽
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LGUISAMPLEPROJECT_API UColorPalatteSaturateAndValueDragArea : public UActorComponent, public ILGUIPointerDragInterface, public ILGUIPointerDownUpInterface
{
	GENERATED_BODY()

public:	
	UColorPalatteSaturateAndValueDragArea();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere)
		AUISpriteActor* _PickerCircleActor;
	UUIItem* _RootUIItem;

public:
	virtual bool OnPointerBeginDrag_Implementation(const FLGUIPointerEventData& eventData)override;
	virtual bool OnPointerDrag_Implementation(const FLGUIPointerEventData& eventData)override;
	virtual bool OnPointerEndDrag_Implementation(const FLGUIPointerEventData& eventData)override;

	virtual bool OnPointerDown_Implementation(const FLGUIPointerEventData& eventData)override;
	virtual bool OnPointerUp_Implementation(const FLGUIPointerEventData& eventData)override;

	FLGUIVector2Delegate SaturateAndValueChangeDelegate;
	void SetSaturateAndValue(float InSaturate, float InValue);
};
