// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameSparks/Private/GSApi.h"
#include "GameSparks/Public/GameSparksModule.h"
#include "GameSparksStatics.generated.h"

/**
 * 
 */
UCLASS()
class CHAOSCORPS_API UGameSparksStatics : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Online List")
		TArray<FString> GetOnlinePlayersList();
	static TArray<FString> playersList;	


	//init the response system
	static void InitStatics(UWorld *myWorld);
	
	//handle login request
	static void LoginRequest_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::AuthenticationResponse &resp);
	//handle login user details request response
	static void LoginSuccessDetails_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::AccountDetailsResponse &resp);
	//handle Registration Request Response
	static void RegistrationRequest_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::RegistrationResponse &resp);
	//handle recieving a list of players
	void GetName_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::LogEventResponse &resp);
	
	
	void UpdateNamesOfOnlinePlayers();

protected:	
	//puts data in string to array of player names
	void parsePlayersString(const std::string& players);
	
private:
	//the world, init at beginplay of gamemode
	static UWorld* theWorld;
	//have we been initialized
	static bool initialized;
	
};