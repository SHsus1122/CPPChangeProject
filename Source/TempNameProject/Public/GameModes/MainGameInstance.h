// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TempNameProject.h"
#include "Engine/GameInstance.h"
#include "Interfaces/SocketInterface.h"
#include "Interfaces/NicknameInterface.h"
#include "Templates/SharedPointer.h"
#include "MainGameInstance.generated.h"

/**
 *
 */
UCLASS()
class TEMPNAMEPROJECT_API UMainGameInstance : public UGameInstance, public ISocketInterface, public INicknameInterface
{
	GENERATED_BODY()

public:
	UMainGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	//================================== [ Create Session ]
	/**
	*	Function to host a game!
	*
	*	@Param		UserID			User that started the request
	*	@Param		SessionName		Name of the Session
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	/**
	*	Function fired when a session create request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);



	//================================== [ Find Session ]
	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/**
	*	Delegate fired when a session search query has completed
	*
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);



	//================================== [ Join Session ]
	/**
	*	Joins a session via a search result
	*
	*	@param SessionName name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool CustomJoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	/**
	*	Delegate fired when a session join request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);



	//================================== [ Delete Session ]
	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	/**
	*	Delegate fired when a destroying an online session has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	virtual void Shutdown() override;



	//================================== [ BlueprintCall Function ]
	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void StartOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void FindOnlineGames();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void JoinOnlineGame(FBlueprintSessionResult SessionResult);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void DestroySessionAndLeaveGame();

public:
	// const TArray<FBlueprintSessionResult>& SessionResults
	// 수정 불가 및 주소값으로 전달함으로 해서 복사는 안 일어나게 세팅 합니다.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnFindSessionResult(const TArray<FBlueprintSessionResult>& SessionResults);

	void OnFindSessionResult_Implementation(const TArray<FBlueprintSessionResult>& SessionResults);

public:
	FString m_UserName;

	UFUNCTION(BlueprintCallable)
	void SetUserName(FString nname) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ShootingGameInstance SetUserName : %s"), *m_UserName));
		m_UserName = nname;
	};

	UFUNCTION(BlueprintPure)
	FString GetUserName() {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("ShootingGameInstance GetUserName : %s"), *m_UserName));
		return m_UserName;
	};



//======================================================
//==================== 소켓 처리 관련 ====================
//======================================================
public:
	/**
	 * Server와 연결되어 있는 FSocket을 Instance에 보관합니다.
	 * @param Socket Server와 연결되어 있는 FSocket.
	 */
	virtual void SetSocket(TSharedPtr<FSocket> Socket) override;

	/**
	 * Instance가 보관하고 있는 Server와 연결된 FSocket을 반환합니다.
	 * @return Server와 연결되어 있는 FSocket.
	 */
	virtual TSharedPtr<FSocket> GetSocket() override;

	/**
	 * Server에서 가져온 Nickname을 Instance에 저장합니다.
	 * @param InNickname Database에서 가져온 Nickname
	 */
	virtual void SetNickname(const FString InNickname) override;

	/**
	 * Instance에 저장되어 있는 Nickname을 가져옵니다.
	 * @return Instance에 저장되어 있는 Nickname
	 */
	UFUNCTION(BlueprintCallable, Category = "Nickname")
	virtual FString GetNickname() override;

protected:
	TSharedPtr<FSocket> ServerSocket;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Nickname;
};
