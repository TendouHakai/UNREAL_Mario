// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushroom.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AMushroom::AMushroom()
{
	GetCharacterMovement()->MaxFlySpeed = 200.f;
	GetCharacterMovement()->bRequestedMoveUseAcceleration = false;
}

void AMushroom::BeginPlay() {
	Super::BeginPlay();

	setState(STATE_MUSHROOM::Start);
}

void AMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (this->state == STATE_MUSHROOM::Start) {
		UE_LOG(LogTemp, Warning, TEXT("run"));
		AddMovementInput(FVector(0.0f, 0.0f, 1.0f), 5);
		if (this->GetTransform().GetLocation().Z > z) {
			setState(STATE_MUSHROOM::Run);
		}
	}
	else AddMovementInput(FVector(1.0f, 0.0f, 0.0f), 1.5);

	
}

void AMushroom::setState(int s)
{
	switch (s)
	{
	case STATE_MUSHROOM::Start:
		z = this->GetTransform().GetLocation().Z + 100.f;

		break;
	case STATE_MUSHROOM::Run:
		GetCapsuleComponent()->SetCollisionProfileName(FName("Pawn"));
		GetCharacterMovement()->MovementMode = MOVE_Walking;
		GetCharacterMovement()->GravityScale = 1.0f;

		//boxComponent->SetPhysicsLinearVelocity(FVector(1.f, 0.f, 0.f));
		break;
	case STATE_MUSHROOM::Collected:
		break;
	default:
		break;
	}

	BaseObject::setState(s);
}
