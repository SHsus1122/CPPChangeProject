// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Entry/EntryPlayerState.h"
#include "GameModes/Entry/EntryPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"


void AEntryPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEntryPlayerState, EntryUserName);
}


AEntryPlayerState::AEntryPlayerState() : MasterVolume(1.0f), MusicVolume(1.0f), SFXVolume(1.0f)
{

}


void AEntryPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}


void AEntryPlayerState::SetUserName(const FString NewUserName)
{
	EntryUserName = NewUserName;

	OnRep_EntryUserName();
}


void AEntryPlayerState::UpdateBind()
{
	AEntryPlayerController* PC = Cast<AEntryPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->BindPlayerState(this);
		return;
	}

	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &AEntryPlayerState::UpdateBind, 0.01f, false);
}


void AEntryPlayerState::OnRep_EntryUserName()
{
	if (OnSetUserName.IsBound())
	{
		OnSetUserName.Broadcast(EntryUserName);
	}
}



//======================================================
//=================== 사운드 처리 관련 ===================
//======================================================
float AEntryPlayerState::ValidateVolume(float Volume)
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


float AEntryPlayerState::GetMasterVolume()
{
	return MasterVolume;
}


void AEntryPlayerState::SetMasterVolume(float Volume)
{
	MasterVolume = ValidateVolume(Volume);
}


float AEntryPlayerState::GetMusicVolume()
{
	return MasterVolume * MusicVolume;
}


void AEntryPlayerState::SetMusicVolume(float Volume)
{
	MusicVolume = ValidateVolume(Volume);
}


float AEntryPlayerState::GetSFXVolume()
{
	return MasterVolume * SFXVolume;
}


void AEntryPlayerState::SetSFXVolume(float Volume)
{
	SFXVolume = ValidateVolume(Volume);
}
