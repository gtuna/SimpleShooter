// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_PlayerLocation.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"


UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "Update Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //returns the first player pawn
	if (PlayerPawn) {

		//set the LastKnownPlayerLocation in the blackboard
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
			PlayerPawn->GetActorLocation());
	}
}
