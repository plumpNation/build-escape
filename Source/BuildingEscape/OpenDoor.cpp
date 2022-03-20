

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

	targetYaw += initialYaw;

	if (!pressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Actor %s"), *GetOwner()->GetName());
	}

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate && pressurePlate->IsOverlappingActor(actorThatOpens)) {
		doorLastOpened = GetWorld()->GetTimeSeconds();

		OpenDoor(DeltaTime);
	}

	if (pressurePlate && !pressurePlate->IsOverlappingActor(actorThatOpens)) {
		float now = GetWorld()->GetTimeSeconds();

		if ((now - doorLastOpened) >= doorCloseDelay) {
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator doorRotation{ 0.f, currentYaw, 0.f };

	currentYaw = FMath::Lerp(currentYaw, targetYaw, DeltaTime * 1.f);
	doorRotation.Yaw = currentYaw;

	GetOwner()->SetActorRotation(doorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator doorRotation{ 0.f, currentYaw, 0.f };

	currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime * 2.f);
	doorRotation.Yaw = currentYaw;

	GetOwner()->SetActorRotation(doorRotation);
}