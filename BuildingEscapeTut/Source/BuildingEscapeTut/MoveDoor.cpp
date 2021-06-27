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
	DoorOpener = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PressurePlate && DoorOpener){
		if(PressurePlate->IsOverlappingActor(DoorOpener)){
			if((GetWorld()->GetTimeSeconds() - doorLastOpened) > doorCloseDelay){
				CloseDoor(DeltaTime);
			}
			
		}else{
			OpenDoor(DeltaTime);
			doorLastOpened = GetWorld()->GetTimeSeconds();
			// UE_LOG(LogTemp, Error, TEXT("Time last opened: %f"), doorLastOpened);
		}
		
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
	currentRotation = FMath::FInterpTo(currentRotation, targetRotation, DeltaTime, DeltaTime*doorSpeed);
	FRotator OpenOutwardsRotation = FRotator();
	OpenOutwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenOutwardsRotation);

	UE_LOG(LogTemp, Warning, TEXT("Object yaw transform after rotating is %f"), (GetOwner()->GetActorRotation()).Yaw);
}

void UMoveDoor::CloseDoor(float DeltaTime){
	// ...
	currentRotation = FMath::FInterpTo(currentRotation, initialRotation, DeltaTime, DeltaTime*doorSpeed);
	FRotator OpenInwardsRotation = FRotator();
	OpenInwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenInwardsRotation);

	UE_LOG(LogTemp, Warning, TEXT("Object yaw transform after rotating is %f"), (GetOwner()->GetActorRotation()).Yaw);
}
