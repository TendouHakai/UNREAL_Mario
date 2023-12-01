// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundEnemyBase.h"
#include "MarioCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"


AGroundEnemyBase::AGroundEnemyBase()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	GetCapsuleComponent()->SetCollisionProfileName(FName("OverlapOnlyPawn"));

	boxCheckFrontComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCheckFront"));
	boxCheckFrontComponent->SetupAttachment(RootComponent);

	boxCheckFlatformComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCheckFlatform"));
	boxCheckFlatformComponent->SetupAttachment(RootComponent);

	// check
	checkfrontComponent = CreateDefaultSubobject<UCheckFrontComponent>(TEXT("checkFrontCode"));
	checkfrontComponent->setBoxComponent(boxCheckFrontComponent);

	checkPlatformComponent = CreateDefaultSubobject<UCheckFlatformComponent>(TEXT("checkFlatform"));
	checkPlatformComponent->setBoxComponent(boxCheckFlatformComponent);
}

void AGroundEnemyBase::BeginPlay() {
	Super::BeginPlay();
}

void AGroundEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AGroundEnemyBase::setState(int s)
{
	Super::setState(s);
}

void AGroundEnemyBase::Move()
{
	if (!isDead) {
		AddMovementInput(FVector(1.0f, 0.f, 0.f), direct);
	}
}

void AGroundEnemyBase::takeDamage()
{
	this->Dead();
}

void AGroundEnemyBase::Dead()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Dead 2"));
	isDead = true;

	FTimerHandle MyTimerHandle;
	GetWorldTimerManager().SetTimer(MyTimerHandle, [this]() {
		Super::Dead();
	}, 2.0f, false);*/

	Super::Dead();
}

UPaperFlipbook* AGroundEnemyBase::getAnimation()
{
	UPaperFlipbook* ani = nullptr;
	if (isDead) {
		ani = DIE_Animation;
	}
	else ani = IDLE_Animation;
	return ani;
}
