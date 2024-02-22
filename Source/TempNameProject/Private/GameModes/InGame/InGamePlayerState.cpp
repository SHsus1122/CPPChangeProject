// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/InGame/InGamePlayerState.h"
#include "GameModes/InGame/InGamePlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

void AInGamePlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGamePlayerState, InGameUserName);
}


AInGamePlayerState::AInGamePlayerState() : MasterVolume(1.0f), MusicVolume(1.0f), SFXVolume(1.0f)
{

}


void AInGamePlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}


void AInGamePlayerState::SetUserName(const FString UserName)
{
	InGameUserName = UserName;

	OnRep_InGameUserName();
}


void AInGamePlayerState::UpdateBind()
{
	AInGamePlayerController* PC = Cast<AInGamePlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->BindPlayerState(this);
		return;
	}

	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &AInGamePlayerState::UpdateBind, 0.01f, false);
}


void AInGamePlayerState::OnRep_InGameUserName()
{
	if (OnSetUserName.IsBound())
	{
		OnSetUserName.Broadcast(InGameUserName);
	}
}



//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
float AInGamePlayerState::ValidateVolume(float Volume)
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


float AInGamePlayerState::GetMasterVolume()
{
	return MasterVolume;
}


void AInGamePlayerState::SetMasterVolume(float Volume)
{
	MasterVolume = ValidateVolume(Volume);
}


float AInGamePlayerState::GetMusicVolume()
{
	return MasterVolume * MusicVolume;
}


void AInGamePlayerState::SetMusicVolume(float Volume)
{
	MusicVolume = ValidateVolume(Volume);
}


float AInGamePlayerState::GetSFXVolume()
{
	return MasterVolume * SFXVolume;
}


void AInGamePlayerState::SetSFXVolume(float Volume)
{
	SFXVolume = ValidateVolume(Volume);
}
