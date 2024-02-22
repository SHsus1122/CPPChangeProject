// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/LobbyPlayerState.h"
#include "GameModes/Lobby/LobbyPlayerController.h"
#include "Net/UnrealNetwork.h"	// DOREPLIFETIME 사용을 위해 추가
#include "Kismet/GameplayStatics.h"

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, LobbyUserName);
}


ALobbyPlayerState::ALobbyPlayerState() : MasterVolume(1.0f), MusicVolume(1.0f), SFXVolume(1.0f)
{

}


void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}


void ALobbyPlayerState::SetUserName(const FString UserName)
{
	LobbyUserName = UserName;

	OnRep_LobbyUserName();
}


void ALobbyPlayerState::UpdateBind()
{
	ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->BindPlayerState(this);
		return;
	}

	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &ALobbyPlayerState::UpdateBind, 0.01f, false);
}


void ALobbyPlayerState::OnRep_LobbyUserName()
{
	if (OnSetUserName.IsBound())
	{
		OnSetUserName.Broadcast(LobbyUserName);
	}
}



//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
float ALobbyPlayerState::ValidateVolume(float Volume)
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


float ALobbyPlayerState::GetMasterVolume()
{
	return MasterVolume;
}


void ALobbyPlayerState::SetMasterVolume(float Volume)
{
	MasterVolume = ValidateVolume(Volume);
}


float ALobbyPlayerState::GetMusicVolume()
{
	return MasterVolume * MusicVolume;
}


void ALobbyPlayerState::SetMusicVolume(float Volume)
{
	MusicVolume = ValidateVolume(Volume);
}


float ALobbyPlayerState::GetSFXVolume()
{
	return MasterVolume * SFXVolume;
}


void ALobbyPlayerState::SetSFXVolume(float Volume)
{
	SFXVolume = ValidateVolume(Volume);
}
