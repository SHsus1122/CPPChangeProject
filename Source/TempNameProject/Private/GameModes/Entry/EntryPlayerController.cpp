// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Entry/EntryPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameModes/MainGameInstance.h"
#include "GameModes/Entry/EntryPlayerState.h"
#include "Home/Public/EntryUserWidget.h"
#include "MainSoundPlugin/Public/MainSoundWidget.h"
#include "ChatPlugin/Public/ChatWidget.h"


AEntryPlayerController::AEntryPlayerController()
{
	BackgroundMusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundMusicComponent"));
	BackgroundMusicComponent->SetupAttachment(RootComponent);

	SFXComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComponent"));
	SFXComponent->SetupAttachment(RootComponent);

	BackgroundMusicComponent->SetVolumeMultiplier(0);
	SFXComponent->SetVolumeMultiplier(0);
}


void AEntryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(EntryWidgetClass);
	if (!IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("IsLocalPlayerController False"));
		return;
	}

	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(Player0))
	{
		return;
	}

	EntryWidget = CreateWidget<UEntryUserWidget>(GetWorld(), EntryWidgetClass);
	EntryWidget->AddToViewport();

	Player0->SetInputMode(FInputModeUIOnly());
	Player0->bShowMouseCursor = true;

	InitializeAudio();
	InitializeWidget();
}


void AEntryPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ResponseClientPossess();
}


void AEntryPlayerController::ResponseClientPossess_Implementation()
{
	UMainGameInstance* GameIns = Cast<UMainGameInstance>(GetGameInstance());
	if (!IsValid(GameIns))
		return;

	AEntryPlayerState* EntryPS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(EntryPS))
	{
		return;
	}

	FString strName = Cast<UMainGameInstance>(GetGameInstance())->GetNickname();
	RequestChangeUserName(strName);
}


void AEntryPlayerController::RequestChangeUserName_Implementation(const FString& NewName)
{
	AEntryPlayerState* EntryPS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(EntryPS))
	{
		return;
	}

	EntryPS->SetUserName(NewName);
}


void AEntryPlayerController::RequestUpdateUserList_Implementation()
{
	ResponseUpdateUserList_Implementation();
}


void AEntryPlayerController::ResponseUpdateUserList_Implementation()
{
	AEntryPlayerState* EntryPlayerState = Cast<AEntryPlayerState>(PlayerState);
	EntryPlayerState->OnRep_EntryUserName();
}


void AEntryPlayerController::BindPlayerState(AEntryPlayerState* EntryPlayerState)
{
	if (IsValid(EntryPlayerState))
	{
		EntryPlayerState->OnSetUserName.AddDynamic(this, &AEntryPlayerController::OnUpdateUserName);
	}
	UpdateUserName();
}


void AEntryPlayerController::UpdateUserName()
{
	if (EntryWidget)
	{
		OnUpdateUserName("");
		return;
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(th_BindPlayerState, this, &AEntryPlayerController::UpdateUserName, 0.01f, false);
}


void AEntryPlayerController::OnUpdateUserName_Implementation(const FString& UserName)
{
}



//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
void AEntryPlayerController::ApplyMasterVolume(float Volume)
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	ApplyMusicVolume(Volume);
	ApplySFXVolume(Volume);
}


void AEntryPlayerController::ApplyMusicVolume(float Volume)
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	BackgroundMusicComponent->SetVolumeMultiplier(Volume);
}


void AEntryPlayerController::ApplySFXVolume(float Volume)
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	SFXComponent->SetVolumeMultiplier(Volume);
	SFXComponent->Play();
}


void AEntryPlayerController::InitializeAudio()
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundMusicClass, PS->GetMusicVolume(), 1.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);

	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundSFXClass, PS->GetSFXVolume(), 1.0f, 1.0f, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);

	BackgroundMusicComponent->SetVolumeMultiplier(1);
	BackgroundMusicComponent->Play();
}


void AEntryPlayerController::InitializeWidget()
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(this->PlayerState);
	if (IsValid(PS))
	{
		float MasterVolume = PS->GetMasterVolume();
		float MusicVolume = PS->GetMusicVolume();
		float SFXVolume = PS->GetSFXVolume();

		SoundWidget = Cast<UMainSoundWidget>(EntryWidget->GetEntrySoundWidget());
		if (!SoundWidget)
		{
			return;
		};
		SoundWidget->OnChangedMasterVolume.AddDynamic(this, &AEntryPlayerController::OnSetMasterVolume);
		SoundWidget->OnChangedMusicVolume.AddDynamic(this, &AEntryPlayerController::OnSetMusicVolume);
		SoundWidget->OnChangedSFXVolume.AddDynamic(this, &AEntryPlayerController::OnSetSFXVolume);

		SoundWidget->SetVolume(MasterVolume, MusicVolume, SFXVolume);
		SoundWidget = SoundWidget;
		SoundWidget->AddToViewport();

		return;
	}
}


void AEntryPlayerController::OnSetMasterVolume_Implementation(float Volume)
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetMasterVolume(Volume);
	ApplyMasterVolume(Volume);
}


void AEntryPlayerController::OnSetMusicVolume_Implementation(float Volume)
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetMusicVolume(Volume);
	ApplyMusicVolume(Volume);
}


void AEntryPlayerController::OnSetSFXVolume_Implementation(float Volume)
{
	AEntryPlayerState* PS = Cast<AEntryPlayerState>(PlayerState);
	if (!IsValid(PS))
		return;

	PS->SetSFXVolume(Volume);
	ApplySFXVolume(Volume);
}