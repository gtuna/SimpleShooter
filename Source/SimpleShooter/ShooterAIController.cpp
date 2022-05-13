// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

        
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),
            this->GetPawn()->GetActorLocation());

        //auto Vec = GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation"));
	}

}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //returns the first player pawn


    if (LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),
            PlayerPawn->GetActorLocation());
    	//set the LastKnownPlayerLocation in the blackboard
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),
			PlayerPawn->GetActorLocation());
         
    }
    else
    {
		//clear player location
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
    
}
