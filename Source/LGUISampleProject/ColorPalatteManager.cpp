// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorPalatteManager.h"
#include "ColorPalatteSaturateAndValueDragArea.h"

void UColorPalatteManager::Awake()
{
	Super::Awake();
	_ColorPickerSaturateAndValueDrag = _ColorPickerSaturateAndValueDragActor->FindComponentByClass<UColorPalatteSaturateAndValueDragArea>();
	_ColorPickerSaturateAndValueDrag->SaturateAndValueChangeDelegate.BindUObject(this, &UColorPalatteManager::OnColorPickerSaturateAndValueChange);
	_ColorPickerSlider = _ColorPickerSliderActor->FindComponentByClass<UUISliderComponent>();
	_ColorPickerSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnColorPickerSliderValueChange));

	_RedSlider = _RedSliderActor->FindComponentByClass<UUISliderComponent>();
	_RedSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnRedSliderValueChange));
	_GreenSlider = _GreenSliderActor->FindComponentByClass<UUISliderComponent>();
	_GreenSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnGreenSliderValueChange));
	_BlueSlider = _BlueSliderActor->FindComponentByClass<UUISliderComponent>();
	_BlueSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnBlueSliderValueChange));

	_HueSlider = _HueSliderActor->FindComponentByClass<UUISliderComponent>();
	_HueSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnHueSliderValueChange));
	_SaturateSlider = _SaturateSliderActor->FindComponentByClass<UUISliderComponent>();
	_SaturateSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnSaturateSliderValueChange));
	_ValueSlider = _ValueSliderActor->FindComponentByClass<UUISliderComponent>();
	_ValueSlider->RegisterSlideEvent(FLGUIFloatDelegate::CreateUObject(this, &UColorPalatteManager::OnValueSliderValueChange));

	ApplyColorChange();
}

void UColorPalatteManager::OnColorPickerSaturateAndValueChange(FVector2D InValue)
{
	auto& newColor = _CurrentColorHSV;
	newColor.Y = InValue.X;
	newColor.Z = InValue.Y;
	ApplyColorChange();
}
void UColorPalatteManager::OnColorPickerSliderValueChange(float InValue)
{
	OnHueSliderValueChange(InValue);
}
void UColorPalatteManager::OnRedSliderValueChange(float InValue)
{
	SliderRGB(0, InValue);
	ApplyColorChange();
}
void UColorPalatteManager::OnGreenSliderValueChange(float InValue)
{
	SliderRGB(1, InValue);
	ApplyColorChange();
}
void UColorPalatteManager::OnBlueSliderValueChange(float InValue)
{
	SliderRGB(2, InValue);
	ApplyColorChange();
}
void UColorPalatteManager::SliderRGB(int index, float InValue)
{
	auto linearColorHSV = FLinearColor(_CurrentColorHSV.X, _CurrentColorHSV.Y, _CurrentColorHSV.Z);
	auto linearColorRGB = linearColorHSV.HSVToLinearRGB();
	switch (index)
	{
	case 0:
	{
		linearColorRGB.R = InValue;
	}
	break;
	case 1:
	{
		linearColorRGB.G = InValue;
	}
	break;
	case 2:
	{
		linearColorRGB.B = InValue;
	}
	break;
	}
	linearColorHSV = linearColorRGB.LinearRGBToHSV();
	_CurrentColorHSV.X = linearColorHSV.R;
	_CurrentColorHSV.Y = linearColorHSV.G;
	_CurrentColorHSV.Z = linearColorHSV.B;
}
void UColorPalatteManager::OnHueSliderValueChange(float InValue)
{
	_CurrentColorHSV.X = InValue;
	ApplyColorChange();
}
void UColorPalatteManager::OnSaturateSliderValueChange(float InValue)
{
	_CurrentColorHSV.Y = InValue;
	ApplyColorChange();
}
void UColorPalatteManager::OnValueSliderValueChange(float InValue)
{
	_CurrentColorHSV.Z = InValue;
	ApplyColorChange();
}

void UColorPalatteManager::ApplyColorChange()
{
	auto oldColorRGB = ColorHSVDataToColorRGB(_OldColorHSV);

	FLinearColor linearColorHSV(_CurrentColorHSV.X, _CurrentColorHSV.Y, _CurrentColorHSV.Z);
	auto linearColorRGB = linearColorHSV.HSVToLinearRGB();
	auto newColorRGB = linearColorRGB.ToFColor(false);
	
	_NewColorActor->GetUISprite()->SetColor(newColorRGB);
	_OldColorActor->GetUISprite()->SetColor(oldColorRGB);

	_RedSlider->SetValue(linearColorRGB.R, false);
	_GreenSlider->SetValue(linearColorRGB.G, false);
	_BlueSlider->SetValue(linearColorRGB.B, false);
	_RedSliderTextureActor->GetUITexture()->SetColor(newColorRGB);
	_GreenSliderTextureActor->GetUITexture()->SetColor(newColorRGB);
	_BlueSliderTextureActor->GetUITexture()->SetColor(newColorRGB);
	_RedSliderTextActor->GetUIText()->SetText(FString::Printf(TEXT("%d"), newColorRGB.R));
	_GreenSliderTextActor->GetUIText()->SetText(FString::Printf(TEXT("%d"), newColorRGB.G));
	_BlueSliderTextActor->GetUIText()->SetText(FString::Printf(TEXT("%d"), newColorRGB.B));

	FLinearColor newColorH_NoSV(_CurrentColorHSV.X, 1.0f, 1.0f);
	auto newColorRGBFromH = newColorH_NoSV.HSVToLinearRGB().ToFColor(false);

	_ColorPickerSlider->SetValue(linearColorHSV.R, false);
	_ColorPickerSaturateAndValueTextureActor->GetUITexture()->SetColor(newColorRGBFromH);
	_ColorPickerSaturateAndValueDrag->SetSaturateAndValue(linearColorHSV.G, linearColorHSV.B);

	_HueSlider->SetValue(linearColorHSV.R, false);
	_SaturateSlider->SetValue(linearColorHSV.G, false);
	_ValueSlider->SetValue(linearColorHSV.B, false);
	float hsv_v = _CurrentColorHSV.Z;
	newColorRGBFromH.R *= hsv_v;
	newColorRGBFromH.G *= hsv_v;
	newColorRGBFromH.B *= hsv_v;
	_SaturateSliderTextureActor->GetUITexture()->SetColor(newColorRGBFromH);
	_ValueSliderTextureActor->GetUITexture()->SetColor(newColorRGB);
	_HueSliderTextActor->GetUIText()->SetText(FString::Printf(TEXT("%d"), (int)(linearColorHSV.R)));
	_SaturateSliderTextActor->GetUIText()->SetText(FString::Printf(TEXT("%d"), (int)(linearColorHSV.G * 255)));
	_ValueSliderTextActor->GetUIText()->SetText(FString::Printf(TEXT("%d"), (int)(linearColorHSV.B * 255)));
}

float UColorPalatteManager::_OneOfUint8 = 1.0f / 255;
FColor UColorPalatteManager::ColorHSVDataToColorRGB(FVector InHSVColor)
{
	FLinearColor colorHSV(InHSVColor);
	return colorHSV.HSVToLinearRGB().ToFColor(false);
}
FVector UColorPalatteManager::ColorRGBToColorHSVData(FColor InRGBColor)
{
	auto linearColorRGB = FLinearColor(InRGBColor.R * _OneOfUint8, InRGBColor.G * _OneOfUint8, InRGBColor.B * _OneOfUint8, 1.0f);
	auto linearColorHSV = linearColorRGB.LinearRGBToHSV();
	return FVector(linearColorHSV);
}
void UColorPalatteManager::Button_Confirm()
{
	_OldColorHSV = _CurrentColorHSV;
	auto oldColorRGB = ColorHSVDataToColorRGB(_OldColorHSV);
	_OldColorActor->GetUISprite()->SetColor(oldColorRGB);
}
void UColorPalatteManager::Button_Close()
{
	ULGUIBPLibrary::DeleteActor(GetOwner());
}