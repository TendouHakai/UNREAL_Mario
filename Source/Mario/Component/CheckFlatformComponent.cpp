// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckFlatformComponent.h"
#include "../Enemy/EnemyBase.h"

// Sets default values for this component's properties
UCheckFlatformComponent::UCheckFlatformComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	//enemy = Cast<AGroundEnemyBase>(GetOwner());
}


// Called when the game starts
void UCheckFlatformComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	box->OnComponentEndOverlap.AddDynamic(this, &UCheckFlatformComponent::OnComponentEndOverlap);
}


// Called every frame
void UCheckFlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCheckFlatformComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemyBase* enemy = Cast<AEnemyBase>(GetOwner());
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic) {
		UE_LOG(LogTemp, Warning, TEXT("end flatform"));
		enemy->setDirect(enemy->getDirect() * (-1));
	}
}

void UCheckFlatformComponent::setBoxComponent(UBoxComponent* boxcomponent)
{
	this->box = boxcomponent;
}

