// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/LobbyGameModeBase.h"
#include "GameModes/Lobby/LobbyGameStateBase.h"
#include "GameModes/Lobby/LobbyPlayerState.h"
#include "GameModes/Lobby/LobbyPlayerController.h"


void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ALobbyGameStateBase* LGS = GetGameState<ALobbyGameStateBase>();
	if (LGS)
	{
		LGS->IncreasePlayerCount();	// PlayerCount UP
		LGS->OnRep_PlayerCount();	// PlayerCount Changed Server Call
	}
}

void ALobbyGameModeBase::Logout(AController* Exiting)
{
	ALobbyGameStateBase* LGS = GetGameState<ALobbyGameStateBase>();
	if (LGS)
	{
		LGS->DecreasePlayerCount();
		LGS->OnRep_PlayerCount();
	}

	Super::Logout(Exiting);
}

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ALobbyGameStateBase* LGS = GetGameState<ALobbyGameStateBase>();
	if (LGS)
	{
		LGS->OnRep_PlayerCount();
	}
}
