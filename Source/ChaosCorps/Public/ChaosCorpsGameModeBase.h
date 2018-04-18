// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameSparks/Private/GameSparksComponent.h"
#include "ChaosCorpsGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class CHAOSCORPS_API AChaosCorpsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type reason);
	
private:
	UPROPERTY(VisibleAnywhere)
		UGameSparksComponent *gameSparks;

	UFUNCTION()
		void OnGameSparksAvailable(bool available);
	
};
