// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

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

    m_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    
    if (m_inputComponent)
    {
        m_inputComponent->BindAction("Use", IE_Pressed, this, &UGrabber::Use);
    }
 
    m_physicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
    if (m_physicsHandleComponent && m_physicsHandleComponent->GrabbedComponent)
    {
        FVector location;
        FRotator rotation;
 
        GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
        FVector target = location + rotation.Vector() * 200.0f;
 
        m_physicsHandleComponent->SetTargetLocation(target);
        m_physicsHandleComponent->SetTargetRotation(rotation);
    }
}

void UGrabber::Use()
{
    UE_LOG(LogTemp, Error, TEXT("Use"));
 
    if (m_physicsHandleComponent && m_physicsHandleComponent->GrabbedComponent)
    {
        Relase();
    }
    else
    {
        Grab();
    }
}
 
void UGrabber::Grab()
{
    FVector location;
    FRotator rotation;
 
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
 
    FVector target = location + rotation.Vector() * 200.0f;
 
    //DrawDebugLine(GetWorld() ,location, target, FColor(255, 0, 0), false, 5.0f, 0, 5.0f);
 
    FHitResult hit;
    GetWorld()->LineTraceSingleByObjectType(hit, location, target, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));
 
    AActor* actorHit = hit.GetActor();
 
    if (actorHit && m_physicsHandleComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("Actor hit: %s"), (*actorHit->GetName()) );
 
        m_physicsHandleComponent->GrabComponentAtLocationWithRotation(hit.GetComponent(), NAME_None, actorHit->GetActorLocation(), actorHit->GetActorRotation());
    }
}
 
void UGrabber::Relase()
{
    m_physicsHandleComponent->ReleaseComponent();
}

