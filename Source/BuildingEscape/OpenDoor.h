

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	public:
		// Sets default values for this component's properties
		UOpenDoor();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	private:
		void OpenDoor(float DeltaTime);
		void CloseDoor(float DeltaTime);

		float initialYaw;
		UPROPERTY(EditAnywhere)
		float openAngle = 90.f;
		float currentYaw;

		UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate;

		AActor* actorThatOpens;

		float doorLastOpened = 0.f;

		UPROPERTY(EditAnywhere)
		float doorCloseDelay = 2.f;
		UPROPERTY(EditAnywhere)
		float doorCloseSpeed = 2.f;
		UPROPERTY(EditAnywhere)
		float doorOpenSpeed = 1.f;
};
