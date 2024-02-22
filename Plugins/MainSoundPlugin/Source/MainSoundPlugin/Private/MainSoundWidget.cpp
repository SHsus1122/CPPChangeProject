// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSoundWidget.h"


void UMainSoundWidget::SetVolume(float InMasterVolume, float InMusiscVolume, float InSFXVolume)
{
	WidgetMasterVolume = InMasterVolume;
	WidgetMusicVolume = InMusiscVolume;
	WidgetSFXVolume = InSFXVolume;
}

void UMainSoundWidget::SetWidgetMasterVolume_Implementation(float Volume)
{
	Volume = ValidateVolume(Volume);
	WidgetMasterVolume = Volume;

	SetWidgetMusicVolume(WidgetMasterVolume);
	SetWidgetSFXVolume(WidgetMasterVolume);
}

void UMainSoundWidget::SetWidgetMusicVolume_Implementation(float Volume)
{
	Volume = ValidateVolume(Volume);
	WidgetMusicVolume = Volume;

	if (OnChangedMusicVolume.IsBound())
	{
		OnChangedMusicVolume.Broadcast(WidgetMusicVolume);
	}
}

void UMainSoundWidget::SetWidgetSFXVolume_Implementation(float Volume)
{
	Volume = ValidateVolume(Volume);
	WidgetSFXVolume = Volume;

	if (OnChangedSFXVolume.IsBound())
	{
		OnChangedSFXVolume.Broadcast(WidgetSFXVolume);
	}
}

float UMainSoundWidget::ValidateVolume(float Volume)
{
	int Max = 1.0f;
	int Min = 0;
	if (Volume > Max)
	{
		Volume = Max;
	}
	else if (Volume < Min)
	{
		Volume = Min;
	}

	return Volume;
}
