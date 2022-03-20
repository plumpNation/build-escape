

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;

	openAngle += initialYaw;

	if (!pressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Actor %s not assigned with a pressure plate"), *GetOwner()->GetName());
	}

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	float now = GetWorld()->GetTimeSeconds();

	if (pressurePlate && pressurePlate->IsOverlappingActor(actorThatOpens)) {
		doorLastOpened = now;

		OpenDoor(deltaTime);
	}

	if (pressurePlate && !pressurePlate->IsOverlappingActor(actorThatOpens)) {
		if ((now - doorLastOpened) >= doorCloseDelay) {
			CloseDoor(deltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float deltaTime)
{
	FRotator doorRotation{ 0.f, currentYaw, 0.f };

	currentYaw = FMath::Lerp(currentYaw, openAngle, deltaTime * doorOpenSpeed);
	doorRotation.Yaw = currentYaw;

	GetOwner()->SetActorRotation(doorRotation);
}

void UOpenDoor::CloseDoor(float deltaTime)
{
	FRotator doorRotation{ 0.f, currentYaw, 0.f };

	currentYaw = FMath::Lerp(currentYaw, initialYaw, deltaTime * doorCloseSpeed);
	doorRotation.Yaw = currentYaw;

	GetOwner()->SetActorRotation(doorRotation);
}