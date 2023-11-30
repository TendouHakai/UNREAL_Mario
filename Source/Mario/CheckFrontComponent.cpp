// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckFrontComponent.h"
#include "GroundEnemyBase.h"
#include "EnemyBase.h"

// Sets default values for this component's properties
UCheckFrontComponent::UCheckFrontComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	
}


// Called when the game starts
void UCheckFrontComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	box->OnComponentBeginOverlap.AddDynamic(this, &UCheckFrontComponent::OnOverlapBegin);
}


// Called every frame
void UCheckFrontComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCheckFrontComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* enemy = Cast<AEnemyBase>(GetOwner());
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic) {
		enemy->setDirect(enemy->getDirect() * (-1));
	}
}

void UCheckFrontComponent::setBoxComponent(UBoxComponent* boxcomponent)
{
	this->box = boxcomponent;
}

