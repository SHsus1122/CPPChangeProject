// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatPlugin/Public/ChatWidget.h"
#include "LobbyPlayerController.generated.h"

class ACharacter;
class USoundMix;
class USoundClass;
class UAudioComponent;
class UUserWidget;
class ULobbyRoomUserWidget;
class UMainSoundWidget;

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

//======================================================
//==================== 공용 처리 관련 ====================
//======================================================
public:
	ALobbyPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION(Client, Reliable)
	void ResponseClientPossess();


	
//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
public:
	// ======================= [ Event Dispatcher Function ]
	/**
	* 전달받은 실수를 통해 전체 볼륨을 조절합니다.
	* @param Volume 전체 볼륨을 조절할 사운드 크기 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetMasterVolume(float Volume);

	/**
	* 전달받은 실수를 통해 전체 볼륨을 조절합니다.
	* @param Volume 전체 볼륨을 조절할 사운드 크기 값
	*/
	virtual void OnSetMasterVolume_Implementation(float Volume);

	/**
	* 전달받은 실수를 통해 음악 볼륨을 조절합니다.
	* @param Volume 음악 볼륨을 조절할 사운드 크기 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetMusicVolume(float Volume);

	/**
	* 전달받은 실수를 통해 음악 볼륨을 조절합니다.
	* @param Volume 음악 볼륨을 조절할 사운드 크기 값
	*/
	virtual void OnSetMusicVolume_Implementation(float Volume);

	/**
	* 전달받은 실수를 통해 효과음 볼륨을 조절합니다.
	* @param Volume 효과음 볼륨을 조절할 사운드 크기 값
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSetSFXVolume(float Volume);

	/**
	* 전달받은 실수를 통해 효과음 볼륨을 조절합니다.
	* @param Volume 효과음 볼륨을 조절할 사운드 크기 값
	*/
	virtual void OnSetSFXVolume_Implementation(float Volume);

private:
	// ======================= [ Member Function ]
	void InitializeAudio();

	void InitializeWidget();

	void ApplyMasterVolume(float Volume);

	void ApplyMusicVolume(float Volume);

	void ApplySFXVolume(float Volume);


	// ======================= [ Member Property ]
	// UI Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TObjectPtr<UMainSoundWidget> SoundWidget;


	// Sound Class, Mix Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Sound")
	TObjectPtr<USoundMix> SoundMix;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Sound")
	TObjectPtr<USoundClass> SoundMusicClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Sound")
	TObjectPtr<USoundClass> SoundSFXClass;


	// UAudioComponent Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "AudioComponents")
	TObjectPtr<UAudioComponent> BackgroundMusicComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "AudioComponents")
	TObjectPtr<UAudioComponent> SFXComponent;



//======================================================
//=============== 플레이어 닉네임 정보 관련 ===============
//======================================================
public:
	UFUNCTION(Server, Reliable)
	void RequestChangeUserName(const FString& NewName);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RequestUpdateUserList();

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ResponseUpdateUserList();


//======================================================
	void BindPlayerState(class ALobbyPlayerState* LobbyPlayerState);

	void UpdateUserName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateUserName(const FString& UserName);

	void OnUpdateUserName_Implementation(const FString& UserName);


//======================================================
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<ULobbyRoomUserWidget> LobbyWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<ULobbyRoomUserWidget> LobbyWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<UChatWidget> ChatWidget;

	FTimerHandle th_BindPlayerState;



//======================================================
//====================== 채팅 관련 ======================
//======================================================
public:
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable)
	void C2S_SendMessage(const FString& InMessage);					// Client Call
	void C2S_SendMessage_Implementation(const FString& InMessage);	// Server Execute
	bool C2S_SendMessage_Validate(const FString& InMessage);

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FString& InMessage);					// Server Call
	void S2C_SendMessage_Implementation(const FString& InMessage);	// Client Execute
};
