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
}
