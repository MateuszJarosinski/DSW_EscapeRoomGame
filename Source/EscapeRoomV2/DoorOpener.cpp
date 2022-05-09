// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

    initialYaw = GetOwner()->GetActorRotation().Yaw;
	
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //AActor* player = GetWorld()->GetFirstPlayerController()->GetPawn();
     
        //if (trigger && trigger->IsOverlappingActor(player))
        //{
        //    UE_LOG(LogTemp, Warning, TEXT("Player in trigger"));
        //    Open(DeltaTime);
        //}
        //else
        //{
        //    Close(DeltaTime);
        //}
     
        bool open = false;
        if (trigger)
        {
            TArray<UPrimitiveComponent*> components;
            trigger->GetOverlappingComponents(components);
     
            for (auto& actor : components)
            {
                if (actor->ComponentHasTag(TEXT("Key")))
                {
                    open = true;
                }
            }
        }
     
        if (open)
        {
            Open(DeltaTime);
        }
        else
        {
            Close(DeltaTime);
        }
}

void UDoorOpener::Open(float DeltaTime)
{
    float currentYaw = GetOwner()->GetActorRotation().Yaw;
 
    currentYaw = FMath::Lerp(currentYaw, initialYaw + openRadius, DeltaTime * openingSpeed);
 
    FRotator rotator = GetOwner()->GetActorRotation();
    rotator.Yaw = currentYaw;
 
    GetOwner()->SetActorRotation(rotator);
}
 
void UDoorOpener::Close(float DeltaTime)
{
    float currentYaw = GetOwner()->GetActorRotation().Yaw;
 
    currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime * openingSpeed);
 
    FRotator rotator = GetOwner()->GetActorRotation();
    rotator.Yaw = currentYaw;
 
    GetOwner()->SetActorRotation(rotator);
}

