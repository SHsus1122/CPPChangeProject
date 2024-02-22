// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

#include "GameModes/Lobby/LobbyPlayerState.h"
#include "GameModes/MainGameInstance.h"

#include "MainSoundWidget.h"
#include "ChatPlugin/Public/ChatWidget.h"
#include "Home/Public/LobbyRoomUserWidget.h"


ALobbyPlayerController::ALobbyPlayerController()
{
	BackgroundMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundMusicComponent"));
	BackgroundMusicComponent->SetupAttachment(RootComponent);

	SFXComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComponent"));
	SFXComponent->SetupAttachment(RootComponent);

	BackgroundMusicComponent->SetVolumeMultiplier(0);
	SFXComponent->SetVolumeMultiplier(0);
}


void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(LobbyWidgetClass);
	//check(ChatWidgetClass);
	if (!IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("IsLocalPlayerController False"));
		return;
	}
	else
	{
		LobbyWidget = CreateWidget<ULobbyRoomUserWidget>(GetWorld(), LobbyWidgetClass);
		LobbyWidget->AddToViewport();

		ChatWidget = Cast<UChatWidget>(LobbyWidget->GetLobbyChatWidget());
	}

	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(Player0))
	{
		return;
	}

	Player0->SetInputMode(FInputModeUIOnly());
	Player0->bShowMouseCursor = true;

	InitializeAudio();
	InitializeWidget();
}


void ALobbyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ResponseClientPossess();
}


void ALobbyPlayerController::ResponseClientPossess_Implementation()
{
	UMainGameInstance* GameIns = Cast<UMainGameInstance>(GetGameInstance());
	if (!IsValid(GameIns))
	{
		return;
	}

	FString strName = Cast<UMainGameInstance>(GetGameInstance())->GetNickname();
	RequestChangeUserName(strName);
}


void ALobbyPlayerController::RequestChangeUserName_Implementation(const FString& NewName)
{
	ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(LobbyPS))
	{
		return;
	}

	LobbyPS->SetUserName(NewName);
}


void ALobbyPlayerController::RequestUpdateUserList_Implementation()
{
	ResponseUpdateUserList_Implementation();
}


void ALobbyPlayerController::ResponseUpdateUserList_Implementation()
{
	ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
	LobbyPlayerState->OnRep_LobbyUserName();
}


void ALobbyPlayerController::BindPlayerState(ALobbyPlayerState* LobbyPlayerState)
{
	if (IsValid(LobbyPlayerState))
	{
		LobbyPlayerState->OnSetUserName.AddDynamic(this, &ALobbyPlayerController::OnUpdateUserName);
	}
	UpdateUserName();
}


void ALobbyPlayerController::UpdateUserName()
{
	if (LobbyWidget)
	{
		OnUpdateUserName("");
		return;
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(th_BindPlayerState, this, &ALobbyPlayerController::UpdateUserName, 0.01f, false);
}


void ALobbyPlayerController::OnUpdateUserName_Implementation(const FString& UserName)
{
}



//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
void ALobbyPlayerController::ApplyMasterVolume(float Volume)
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	ApplyMusicVolume(Volume);
	ApplySFXVolume(Volume);
}


void ALobbyPlayerController::ApplyMusicVolume(float Volume)
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	BackgroundMusicComponent->SetVolumeMultiplier(Volume);
}


void ALobbyPlayerController::ApplySFXVolume(float Volume)
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	SFXComponent->SetVolumeMultiplier(Volume);
	SFXComponent->Play();
}


void ALobbyPlayerController::InitializeAudio()
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundMusicClass, PS->GetMusicVolume(), 1.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);

	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundSFXClass, PS->GetSFXVolume(), 1.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);

	BackgroundMusicComponent->SetVolumeMultiplier(1);
	BackgroundMusicComponent->Play();
}


void ALobbyPlayerController::InitializeWidget()
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(this->PlayerState);
	if (IsValid(PS))
	{
		float MasterVolume = PS->GetMasterVolume();
		float MusicVolume = PS->GetMusicVolume();
		float SFXVolume = PS->GetSFXVolume();

		SoundWidget = Cast<UMainSoundWidget>(LobbyWidget->GetLobbySoundWidget());
		if (!SoundWidget)
		{
			return;
		}
		SoundWidget->OnChangedMasterVolume.AddDynamic(this, &ALobbyPlayerController::OnSetMasterVolume);
		SoundWidget->OnChangedMusicVolume.AddDynamic(this, &ALobbyPlayerController::OnSetMusicVolume);
		SoundWidget->OnChangedSFXVolume.AddDynamic(this, &ALobbyPlayerController::OnSetSFXVolume);

		SoundWidget->SetVolume(MasterVolume, MusicVolume, SFXVolume);
		SoundWidget = SoundWidget;
		SoundWidget->AddToViewport();

		return;
	}
}


void ALobbyPlayerController::OnSetMasterVolume_Implementation(float Volume)
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetMasterVolume(Volume);
	ApplyMasterVolume(Volume);
}


void ALobbyPlayerController::OnSetMusicVolume_Implementation(float Volume)
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetMusicVolume(Volume);
	ApplyMusicVolume(Volume);
}


void ALobbyPlayerController::OnSetSFXVolume_Implementation(float Volume)
{
	ALobbyPlayerState* PS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetSFXVolume(Volume);
	ApplySFXVolume(Volume);
}



//======================================================
//====================== 채팅 관련 ======================
//======================================================
bool ALobbyPlayerController::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}


void ALobbyPlayerController::C2S_SendMessage_Implementation(const FString& InMessage)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ALobbyPlayerController* LPC = Cast<ALobbyPlayerController>(*It);
		if (LPC)
		{
			LPC->S2C_SendMessage(InMessage);
		}
	}
}


// Execute Client
void ALobbyPlayerController::S2C_SendMessage_Implementation(const FString& InMessage)
{
	if (ChatWidget)
	{
		ChatWidget->AddMessage(InMessage);
	}
}