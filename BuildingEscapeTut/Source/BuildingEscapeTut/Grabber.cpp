// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay(){
	Super::BeginPlay();

	// ...
	SetupPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Determining maximum raytrace depth
	if (PhysicsHandle->GetGrabbedComponent())
	{
		FVector PhysicsObjectLocation = GetRayTraceEnd();
		PhysicsHandle->SetTargetLocation(PhysicsObjectLocation);
	}
}

// Find the InputComponent instance attached to the Actor/Player
void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent){
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
	}else{
		UE_LOG(LogTemp, Error, TEXT("No Input Component found!"));
	}
}

void UGrabber::SetupPhysicsHandle(){

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr){
		UE_LOG(LogTemp, Error, TEXT("No physics handle found!"));
	}
}

void UGrabber::Grab(){
	FVector TargetObjectPosition = GetRayTraceEnd();
	FHitResult TargetObject = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent *ComponentToGrab = TargetObject.GetComponent();

	if (TargetObject.GetActor()){
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, TargetObjectPosition);
	}
}

void UGrabber::Release(){

	if (PhysicsHandle->GetGrabbedComponent()){
		PhysicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("Released Physical Object"));
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{

	FVector PlayerViewPointLocation;
	FVector LineEnd = GetRayTraceEnd();
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPointLocation,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);
	AActor *ActorHit = HitResult.GetActor();

	return HitResult;
}

FVector UGrabber::GetRayTraceEnd() const{

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	// Ray-cast out to a certain distance (Reach)
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return LineTraceEnd;
}