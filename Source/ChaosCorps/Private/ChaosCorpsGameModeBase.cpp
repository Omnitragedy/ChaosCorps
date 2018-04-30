// Fill out your copyright notice in the Description page of Project Settings.

#include "ChaosCorpsGameModeBase.h"
#include "ChaosCorps.h"
#include "GameSparks/Public/GameSparksModule.h"
#include "CCStateManager.h"
#include "GameSparksStatics.h"

void AChaosCorpsGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	gameSparks = NewObject<UGameSparksComponent>(this, FName("GameSparks Component"));

	//check if gamesparks module available
	if (!UGameSparksModule::GetModulePtr()->IsInitialized()) {
		//delegate for conn/disconn
		gameSparks->OnGameSparksAvailableDelegate.AddDynamic(this, &AChaosCorpsGameModeBase::OnGameSparksAvailable);

		//force disconnect before attempting to connect for safety and then connect
		gameSparks->Disconnect();
		gameSparks->Connect(FString("o352423DGsUf"), FString("jUfp3gnc0LWfZiCXrrBNMZcfvvaznCeB"), true, false); //key, secret
	}

	//init statics
	UGameSparksStatics::InitStatics(GetWorld());
}

void AChaosCorpsGameModeBase::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);

	if (gameSparks) {
		gameSparks->Disconnect();
	}
}

void AChaosCorpsGameModeBase::OnGameSparksAvailable(bool available)
{
	if (available) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Gamesparks available"));
		}

		//show login screen if connection success
		if (GetWorld()->GetGameInstance()) {
			UCCStateManager *stateManager = Cast<UCCStateManager>(GetWorld()->GetGameInstance());

			//change to login state
			stateManager->ChangeState(EGameState::ELoginScreen);
		}
	}
	else
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Gamesparks connection lost"));
		}
	}
}
