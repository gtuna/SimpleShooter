// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //returns the first player pawn

	if (PlayerPawn == nullptr)
	{
		return;
	}

	if (OwnerComp.GetAIOwner() ==nullptr)
	{
		return;
	}

//	AShooterAIController* ShooterAIController = Cast<AShooterAIController>(PlayerPawn->GetController());

	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		//set the LastKnownPlayerLocation in the blackboard
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
			PlayerPawn->GetActorLocation());	
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	

}
