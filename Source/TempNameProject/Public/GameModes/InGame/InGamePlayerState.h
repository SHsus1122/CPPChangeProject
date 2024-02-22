// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainSoundInterface.h"
#include "GameFramework/PlayerState.h"
#include "InGamePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInGameUserName, const FString&, UserName);

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AInGamePlayerState : public APlayerState, public IMainSoundInterface
{
	GENERATED_BODY()

public:
	AInGamePlayerState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void SetUserName(const FString UserName);

	UFUNCTION(BlueprintCallable)
	void UpdateBind();

public:
	UFUNCTION(BlueprintCallable)
	void OnRep_InGameUserName();

	UFUNCTION(BlueprintPure)
	FString GetStrUserName() { return InGameUserName; };

public:
	UPROPERTY(ReplicatedUsing = OnRep_InGameUserName)
	FString InGameUserName;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FInGameUserName OnSetUserName;

	FTimerHandle th_UpdateBind;



	//======================================================
	//=================== 사운드 처리 관련 ===================
	//======================================================
public:
	/**
	* 유저의 현재 전체 볼륨의 수치를 가져옵니다.
	* @return 현재 전체 볼륨 수치 실수 값
	*/
	float GetMasterVolume();

	/**
	* 유저의 현재 음악 볼륨의 수치를 가져옵니다.
	* @return 현재 음악 볼륨 수치 실수 값
	*/
	float GetMusicVolume();

	/**
	* 유저의 현재 효과음 볼륨의 수치를 가져옵니다.
	* @return 현재 효과음 볼륨 수치 실수 값
	*/
	float GetSFXVolume();

	/**
	* 유저의 전체 볼륨 수치를 조절합니다.
	* @return 변경할 전체 볼륨 수치 실수 값
	*/
	void SetMasterVolume(float Volume);

	/**
	* 유저의 음악 볼륨 수치를 조절합니다.
	* @return 변경할 음악 볼륨 수치 실수 값
	*/
	void SetMusicVolume(float Volume);

	/**
	* 유저의 효과음 볼륨 수치를 조절합니다.
	* @return 변경할 효과음 볼륨 수치 실수 값
	*/
	void SetSFXVolume(float Volume);


private:
	// ======================= [ Member Function ]
	float ValidateVolume(float Volume);


	// ======================= [ Member Property ]
	// Sound Property
	UPROPERTY(VisibleAnywhere, Category = "Volume")
	float MasterVolume;

	UPROPERTY(VisibleAnywhere, Category = "Volume")
	float MusicVolume;

	UPROPERTY(VisibleAnywhere, Category = "Volume")
	float SFXVolume;

};