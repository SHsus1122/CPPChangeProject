// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/InGame/InGamePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

#include "GameModes/InGame/InGamePlayerState.h"
#include "GameModes/MainGameInstance.h"

#include "MainSoundWidget.h"
#include "ChatPlugin/Public/ChatWidget.h"
#include "Home/Public/InGameUserWidget.h"


AInGamePlayerController::AInGamePlayerController()
{
	BackgroundMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundMusicComponent"));
	BackgroundMusicComponent->SetupAttachment(RootComponent);

	SFXComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComponent"));
	SFXComponent->SetupAttachment(RootComponent);

	BackgroundMusicComponent->SetVolumeMultiplier(0);
	SFXComponent->SetVolumeMultiplier(0);
}

void AInGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ResponseClientPossess();
}

void AInGamePlayerController::ResponseClientPossess_Implementation()
{
	UMainGameInstance* GameIns = Cast<UMainGameInstance>(GetGameInstance());
	if (!IsValid(GameIns))
	{
		return;
	}
	
	FString strName = Cast<UMainGameInstance>(GetGameInstance())->GetNickname();
	RequestChangeUserName(strName);
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InGameWidgetClass);

	if (!IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("IsLocalPlayerController False"));
		return;
	}
	else
	{
		InGameWidget = CreateWidget<UInGameUserWidget>(GetWorld(), InGameWidgetClass);
		InGameWidget->AddToViewport();

		ChatWidget = Cast<UChatWidget>(InGameWidget->GetInGameChatWidget());
	}

	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(Player0))
	{
		return;
	}

	Player0->SetInputMode(FInputModeGameOnly());
	Player0->bShowMouseCursor = false;

	InitializeAudio();
	InitializeWidget();
}


void AInGamePlayerController::RequestChangeUserName_Implementation(const FString& NewName)
{
	AInGamePlayerState* InGamePS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(InGamePS)) {
		return;
	}

	InGamePS->SetUserName(NewName);
	PlayerName = NewName;
}


void AInGamePlayerController::RequestUpdateUserList_Implementation()
{
	ResponseUpdateUserList_Implementation();
}


void AInGamePlayerController::ResponseUpdateUserList_Implementation()
{
	AInGamePlayerState* InGamePlayerState = Cast<AInGamePlayerState>(PlayerState);
	InGamePlayerState->OnRep_InGameUserName();
}


void AInGamePlayerController::BindPlayerState(AInGamePlayerState* InGamePlayerState)
{
	if (IsValid(InGamePlayerState))
	{
		InGamePlayerState->OnSetUserName.AddDynamic(this, &AInGamePlayerController::OnUpdateUserName);
	}
	UpdateUserName();
}


void AInGamePlayerController::UpdateUserName()
{
	if (InGameWidget)
	{
		OnUpdateUserName("");
		return;
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(th_BindPlayerState, this, &AInGamePlayerController::UpdateUserName, 0.01f, false);
}


void AInGamePlayerController::OnUpdateUserName_Implementation(const FString& UserName)
{
}



//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
void AInGamePlayerController::ApplyMasterVolume(float Volume)
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	ApplyMusicVolume(Volume);
	ApplySFXVolume(Volume);
}

void AInGamePlayerController::ApplyMusicVolume(float Volume)
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	BackgroundMusicComponent->SetVolumeMultiplier(Volume);
}

void AInGamePlayerController::ApplySFXVolume(float Volume)
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	SFXComponent->SetVolumeMultiplier(Volume);
	SFXComponent->Play();
}

void AInGamePlayerController::InitializeAudio()
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundMusicClass, PS->GetMusicVolume(), 0.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);

	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundSFXClass, PS->GetSFXVolume(), 0.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);

	BackgroundMusicComponent->SetVolumeMultiplier(1);
	BackgroundMusicComponent->Play();
}

void AInGamePlayerController::InitializeWidget()
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(this->PlayerState);
	if (IsValid(PS))
	{
		float MasterVolume = PS->GetMasterVolume();
		float MusicVolume = PS->GetMusicVolume();
		float SFXVolume = PS->GetSFXVolume();

		SoundWidget = Cast<UMainSoundWidget>(InGameWidget->GetInGameSoundWidget());
		if (!SoundWidget)
		{
			return;
		}
		SoundWidget->OnChangedMasterVolume.AddDynamic(this, &AInGamePlayerController::OnSetMasterVolume);
		SoundWidget->OnChangedMusicVolume.AddDynamic(this, &AInGamePlayerController::OnSetMusicVolume);
		SoundWidget->OnChangedSFXVolume.AddDynamic(this, &AInGamePlayerController::OnSetSFXVolume);

		SoundWidget->SetVolume(MasterVolume, MusicVolume, SFXVolume);
		SoundWidget->AddToViewport();

		return;
	}
}


void AInGamePlayerController::OnSetMasterVolume_Implementation(float Volume)
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetMasterVolume(Volume);
	ApplyMasterVolume(Volume);
}

void AInGamePlayerController::OnSetMusicVolume_Implementation(float Volume)
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetMusicVolume(Volume);
	ApplyMusicVolume(Volume);
}

void AInGamePlayerController::OnSetSFXVolume_Implementation(float Volume)
{
	AInGamePlayerState* PS = Cast<AInGamePlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetSFXVolume(Volume);
	ApplySFXVolume(Volume);
}


//======================================================
//====================== 채팅 관련 ======================
//======================================================
bool AInGamePlayerController::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}


void AInGamePlayerController::C2S_SendMessage_Implementation(const FString& InMessage)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AInGamePlayerController* IPC = Cast<AInGamePlayerController>(*It);
		if (IPC)
		{
			IPC->S2C_SendMessage(InMessage);
		}
	}
}


// Execute Client
void AInGamePlayerController::S2C_SendMessage_Implementation(const FString& InMessage)
{
	if (ChatWidget)
	{
		ChatWidget->AddMessage(InMessage);
	}
}