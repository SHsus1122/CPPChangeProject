// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainSoundInterface.generated.h"

/**
 * 사운드 관련한 기능들을 명시해놓은 사용하는 인터페이스 입니다.
 */
UINTERFACE(Blueprintable)
class UMainSoundInterface : public UInterface
{
	GENERATED_BODY()
};

class MAINSOUNDPLUGIN_API IMainSoundInterface
{
	GENERATED_BODY()

public:
	/**
	* 전체 볼륨 값을 가져올 때 사용합니다.
	* @return 현재 전체 볼륨 실수 값을 가져옵니다.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	float GetMasterVolume();

	/**
	* 전체 볼륨 값을 조절할 때 사용합니다.
	* @param Volume 조절할 전체 볼륨 실수 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	void SetMasterVolume(float Volume);

	/**
	* 음악 볼륨 값을 가져올 때 사용합니다.
	* @return 현재 음악 볼륨 실수 값을 가져옵니다.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	float GetMusicVolume();

	/**
	* 음악 볼륨 값을 조절할 때 사용합니다.
	* @param Volume 조절할 음악 볼륨 실수 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	void SetMusicVolume(float Volume);

	/**
	* 효과음 볼륨 값을 가져올 때 사용합니다.
	* @return 현재 효과음 볼륨 실수 값을 가져옵니다.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	float GetSFXVolume();

	/**
	* 효과음 볼륨 값을 조절할 때 사용합니다.
	* @param Volume 조절할 효과음 볼륨 실수 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Volume")
	void SetSFXVolume(float Volume);
};
