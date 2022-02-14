// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LGUIHeaders.h"
#include "ColorPalatteManager.generated.h"


//调色工具
UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class LGUISAMPLEPROJECT_API UColorPalatteManager : public ULGUILifeCycleUIBehaviour
{
	GENERATED_BODY()

protected:
	virtual void Awake() override;

	FVector _CurrentColorHSV = FVector(0, 1.0f, 1.0f);
	FVector _OldColorHSV = FVector(0, 1.0f, 1.0f);
	//color picker
	UPROPERTY(EditAnywhere)
		AActor* _ColorPickerSaturateAndValueDragActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _ColorPickerSaturateAndValueTextureActor;
	UPROPERTY(EditAnywhere)
		AActor* _ColorPickerSliderActor;
	//rgb
	UPROPERTY(EditAnywhere)
		AActor* _RedSliderActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _RedSliderTextureActor;
	UPROPERTY(EditAnywhere)
		AUITextActor* _RedSliderTextActor;
	UPROPERTY(EditAnywhere)
		AActor* _GreenSliderActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _GreenSliderTextureActor;
	UPROPERTY(EditAnywhere)
		AUITextActor* _GreenSliderTextActor;
	UPROPERTY(EditAnywhere)
		AActor* _BlueSliderActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _BlueSliderTextureActor;
	UPROPERTY(EditAnywhere)
		AUITextActor* _BlueSliderTextActor;
	//hsv
	UPROPERTY(EditAnywhere)
		AActor* _HueSliderActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _HueSliderTextureActor;
	UPROPERTY(EditAnywhere)
		AUITextActor* _HueSliderTextActor;
	UPROPERTY(EditAnywhere)
		AActor* _SaturateSliderActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _SaturateSliderTextureActor;
	UPROPERTY(EditAnywhere)
		AUITextActor* _SaturateSliderTextActor;
	UPROPERTY(EditAnywhere)
		AActor* _ValueSliderActor;
	UPROPERTY(EditAnywhere)
		AUITextureActor* _ValueSliderTextureActor;
	UPROPERTY(EditAnywhere)
		AUITextActor* _ValueSliderTextActor;
	//new old color
	UPROPERTY(EditAnywhere)
		AUISpriteActor* _NewColorActor;
	UPROPERTY(EditAnywhere)
		AUISpriteActor* _OldColorActor;
	
	class UColorPalatteSaturateAndValueDragArea* _ColorPickerSaturateAndValueDrag;
	UUISliderComponent* _ColorPickerSlider, *_RedSlider, *_GreenSlider, *_BlueSlider, *_HueSlider, *_SaturateSlider, *_ValueSlider;
	UUISprite* _ColorPickerDrag;

	void OnColorPickerSaturateAndValueChange(FVector2D InValue);
	void OnColorPickerSliderValueChange(float InValue);
	void OnRedSliderValueChange(float InValue);
	void OnGreenSliderValueChange(float InValue);
	void OnBlueSliderValueChange(float InValue);
	void OnHueSliderValueChange(float InValue);
	void OnSaturateSliderValueChange(float InValue);
	void OnValueSliderValueChange(float InValue);

	void SliderRGB(int index, float InValue);

	void ApplyColorChange();

	static float _OneOfUint8;
public:	
	UFUNCTION()void Button_Confirm();
	UFUNCTION()void Button_Close();

	static FColor ColorHSVDataToColorRGB(FVector InHSVColor);
	static FVector ColorRGBToColorHSVData(FColor InRGBColor);
};
