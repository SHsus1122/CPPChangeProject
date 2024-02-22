// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/InGame/InGameModeBase.h"
#include "GameModes/InGame/InGameStateBase.h"
#include "GameModes/InGame/InGamePlayerState.h"
#include "GameModes/InGame/InGamePlayerController.h"

void AInGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AInGameStateBase* IGS = GetGameState<AInGameStateBase>();
	if (IGS)
	{
		IGS->IncreasePlayerCount();
		IGS->OnRep_PlayerCount();
	}
}

void AInGameModeBase::Logout(AController* Exiting)
{
	AInGameStateBase* IGS = GetGameState<AInGameStateBase>();
	if (IGS)
	{
		IGS->DecreasePlayerCount();
		IGS->OnRep_PlayerCount();
	}

	AInGamePlayerState* PS = Exiting->GetPlayerState<AInGamePlayerState>();
	PS->OnRep_InGameUserName();

	Super::Logout(Exiting);
}

void AInGameModeBase::RequestLogoutInfo_Implementation(AInGamePlayerState* InPlayerState)
{
	ResponseLogoutInfo(InPlayerState);
}

void AInGameModeBase::ResponseLogoutInfo_Implementation(AInGamePlayerState* InPlayerState)
{
	GetLogoutPlayerState(InPlayerState);
}

AInGamePlayerState* AInGameModeBase::GetLogoutPlayerState(AInGamePlayerState* InPlayerState)
{
	return InPlayerState;
}

void AInGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AInGameStateBase* IGS = GetGameState<AInGameStateBase>();
	if (IGS)
	{
		IGS->OnRep_PlayerCount();
	}
}
