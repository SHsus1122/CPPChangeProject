// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainSoundWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMasterVolumeDelegate, float, WidgetMasterVolume);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMusicVolumeDelegate, float, WidgetMusicVolume);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSFXVolumeDelegate, float, WidgetSFXVolume);

/**
 * SoundWidget 에서 다루게 될 UserWidget 클래스 입니다.
 */
UCLASS()
class MAINSOUNDPLUGIN_API UMainSoundWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetVolume(float MasterVolume, float MusicVolume, float SFXVolume);

	// ======================= [ Event Dispatcher Function ]
	/**
	* 전달받은 실수를 통해 전체 볼륨을 조절합니다.
	* @param Volume 전체 볼륨을 조절할 사운드 크기 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	void SetWidgetMasterVolume(float Volume);

	/**
	* 전달받은 실수를 통해 전체 볼륨을 조절합니다.
	* @param Volume 전체 볼륨을 조절할 사운드 크기 값
	*/
	void SetWidgetMasterVolume_Implementation(float Volume);

	/**
	* 전달받은 실수를 통해 음악 볼륨을 조절합니다.
	* @param Volume 음악 볼륨을 조절할 사운드 크기 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	void SetWidgetMusicVolume(float Volume);

	/**
	* 전달받은 실수를 통해 음악 볼륨을 조절합니다.
	* @param Volume 음악 볼륨을 조절할 사운드 크기 값
	*/
	void SetWidgetMusicVolume_Implementation(float Volume);

	/**
	* 전달받은 실수를 통해 효과음 볼륨을 조절합니다.
	* @param Volume 효과음 볼륨을 조절할 사운드 크기 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	void SetWidgetSFXVolume(float Volume);

	/**
	* 전달받은 실수를 통해 효과음 볼륨을 조절합니다.
	* @param Volume 효과음 볼륨을 조절할 사운드 크기 값
	*/
	void SetWidgetSFXVolume_Implementation(float Volume);


	// ======================= [ Member Function ]
	/**
	* 전달받은 실수를 볼륨의 최소치와 최대치를 벗어나지 않게 검증합니다.
	* @param Volume 유저가 조절하고자 하는 볼륨 수치
	* @return 검증 이후 나온 결과, 실수 값
	*/
	float ValidateVolume(float Volume);


	// ======================= [ Delegate Property ]
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float WidgetMasterVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float WidgetMusicVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	float WidgetSFXVolume;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Volume")
	FMasterVolumeDelegate OnChangedMasterVolume;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Volume")
	FMusicVolumeDelegate OnChangedMusicVolume;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Volume")
	FSFXVolumeDelegate OnChangedSFXVolume;

protected:


private:

};
