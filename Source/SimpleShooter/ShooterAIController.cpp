// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();


}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //returns the first player pawn
    
    SetFocus(PlayerPawn); 
    MoveToActor(PlayerPawn, 200);
    
}
