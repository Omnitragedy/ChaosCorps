// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CCStateManager.generated.h"


//enum for top level states
UENUM(BlueprintType)
enum class EGameState : uint8 {
	ENone			UMETA(DisplayName = "None"),
	EStartup		UMETA(DisplayName = "Startup"),
	ELoginScreen	UMETA(DisplayName = "LoginScreen"),
};

/**
 * 
 */
UCLASS()
class CHAOSCORPS_API UCCStateManager : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly, Category = "State Manager")
		TSubclassOf<class UUserWidget> cLoginMenu;

	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable, Category = "State Manager")
		void ChangeState(EGameState newState);

	//returns current game state
	EGameState GetGameState();
	
	/*GAMESPARKS CALLS*/
	void Login(FString username, FString password);
	void Register(FString username, FString password);
	/*END GAMESPARKS CALLS*/

private:
	//currently displayed widget
	UUserWidget *currentWidget;

	//current game state
	EGameState currentState;
	
	void EnterState(EGameState newState);
	void LeaveState(EGameState oldState);
};
