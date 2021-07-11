// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber available"));

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// UE_LOG(LogTemp, Warning, TEXT("Player View Point Location: %s \n Player View Point Rotation: %s "), 
	// *PlayerViewPointLocation.ToString(),
	// *PlayerViewPointRotation.ToString());
	// ...

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0, 0.5f);

	//Struct, not a variable
	//Reference: https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/FCollisionQueryParams/
	FCollisionQueryParams CollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation, 
		LineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		CollisionQueryParams);

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	AActor* ActorHit = HitResult.GetActor();

	if(PhysicsHandle){
		UE_LOG(LogTemp, Warning, TEXT("Found Physics Handle component %s"), *(PhysicsHandle->GetName()));
	}else{
		UE_LOG(LogTemp, Error, TEXT("No physics handle found!"));
	}
	
	if(ActorHit){
		UE_LOG(LogTemp, Warning, TEXT("Raycast Hit %s"), *(ActorHit->GetName()));
	}else{
		UE_LOG(LogTemp, Error, TEXT("Raycast Hit nothing!"));
	}
	
}

