// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMV2_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* trigger = nullptr;
 
    UPROPERTY(EditAnywhere)
    float openingSpeed = 0.0f;
 
    UPROPERTY(EditAnywhere)
    float openRadius = 90.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void Open(float DeltaTime);
    void Close(float DeltaTime);
 
    float initialYaw = 0.0f;
		
};
