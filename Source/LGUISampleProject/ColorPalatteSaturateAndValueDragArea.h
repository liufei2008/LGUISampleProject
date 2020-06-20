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

protected:

	UPROPERTY(EditAnywhere)
		AUISpriteActor* _PickerCircleActor;
	UUIItem* _RootUIItem;

public:
	virtual bool OnPointerBeginDrag_Implementation(ULGUIPointerEventData* eventData)override;
	virtual bool OnPointerDrag_Implementation(ULGUIPointerEventData* eventData)override;
	virtual bool OnPointerEndDrag_Implementation(ULGUIPointerEventData* eventData)override;

	virtual bool OnPointerDown_Implementation(ULGUIPointerEventData* eventData)override;
	virtual bool OnPointerUp_Implementation(ULGUIPointerEventData* eventData)override;

	FLGUIVector2Delegate SaturateAndValueChangeDelegate;
	void SetSaturateAndValue(float InSaturate, float InValue);
};
