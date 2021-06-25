// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveDoor.h"

// Sets default values for this component's properties
UMoveDoor::UMoveDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveDoor::BeginPlay()
{
	Super::BeginPlay();

	currentRotation = GetOwner()->GetActorRotation().Yaw;
	initialRotation = currentRotation;
	targetRotation = initialRotation + doorOpenRotation;
	UE_LOG(LogTemp, Warning, TEXT("Object yaw transform before rotating is %f"), (GetOwner()->GetActorRotation()).Yaw);

}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PressurePlate && DoorOpener && PressurePlate->IsOverlappingActor(DoorOpener)){
		OpenDoor(DeltaTime);
	}
	if(!DoorOpener){
		UE_LOG(LogTemp, Error, TEXT("NO DoorOpener assigned!"));
	}
	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("NO PressurePlate assigned!"));
	}
	//TODO: Try using actor's name for better logging
}

void UMoveDoor::OpenDoor(float DeltaTime){
	// ...
	currentRotation = FMath::FInterpTo(currentRotation, targetRotation, DeltaTime, DeltaTime*60);
	FRotator OpenOutwardsRotation = FRotator();
	OpenOutwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenOutwardsRotation);

	UE_LOG(LogTemp, Warning, TEXT("Object yaw transform after rotating is %f"), (GetOwner()->GetActorRotation()).Yaw);
}
