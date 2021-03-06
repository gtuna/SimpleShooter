// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "KillEmAllGameMode.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}



	// for loop over ShooterAI in World
	for (AShooterAIController* ShooterAIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!ShooterAIController->IsDead())
		{
			return;
		}
	}

	EndGame(true); 

}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

