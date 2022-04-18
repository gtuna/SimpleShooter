// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//DrawDebugCamera(GetWorld(), EyeLocation, EyeRotation, 90, 2, FColor::Red, true);

	FVector End = Location + Rotation.Vector() * MaxRange;
	FHitResult HitResult;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess && HitResult.bBlockingHit)
	{
		//DrawDebugPoint(GetWorld(), HitResult.Location , 20, FColor::Red, true);

		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());

		AActor* HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

