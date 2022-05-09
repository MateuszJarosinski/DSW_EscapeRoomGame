// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootDoorOpener.h"

// Sets default values for this component's properties
UShootDoorOpener::UShootDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootDoorOpener::BeginPlay()
{
	Super::BeginPlay();

    initialYaw = GetOwner()->GetActorRotation().Yaw;
	
}


// Called every frame
void UShootDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    bool open1 = true;
    bool open2 = true;
    bool open3 = true;
    if (trigger1)
    {
        TArray<UPrimitiveComponent*> components;
        trigger1->GetOverlappingComponents(components);

        for (auto& actor : components)
        {
            if (actor->ComponentHasTag(TEXT("Key")))
            {
                open1 = false;
            }
        }
    }
    if (trigger2)
    {
        TArray<UPrimitiveComponent*> components;
        trigger2->GetOverlappingComponents(components);

        for (auto& actor : components)
        {
            if (actor->ComponentHasTag(TEXT("Key")))
            {
                open2 = false;
            }
        }
    }
    if (trigger3)
    {
        TArray<UPrimitiveComponent*> components;
        trigger3->GetOverlappingComponents(components);

        for (auto& actor : components)
        {
            if (actor->ComponentHasTag(TEXT("Key")))
            {
                open3 = false;
            }
        }
    }

    if (open1&&open2&&open3)
    {
        Open(DeltaTime);
    }
    else
    {
        Close(DeltaTime);
    }
}

void UShootDoorOpener::Open(float DeltaTime)
{
    float currentYaw = GetOwner()->GetActorRotation().Yaw;

    currentYaw = FMath::Lerp(currentYaw, initialYaw + openRadius, DeltaTime * openingSpeed);

    FRotator rotator = GetOwner()->GetActorRotation();
    rotator.Yaw = currentYaw;

    GetOwner()->SetActorRotation(rotator);
}

void UShootDoorOpener::Close(float DeltaTime)
{
    float currentYaw = GetOwner()->GetActorRotation().Yaw;

    currentYaw = FMath::Lerp(currentYaw, initialYaw, DeltaTime * openingSpeed);

    FRotator rotator = GetOwner()->GetActorRotation();
    rotator.Yaw = currentYaw;

    GetOwner()->SetActorRotation(rotator);
}

