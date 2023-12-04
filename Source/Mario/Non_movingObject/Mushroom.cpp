// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushroom.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "../MarioCharacter.h"

AMushroom::AMushroom()
{
	GetCharacterMovement()->MaxFlySpeed = 200.f;
	GetCharacterMovement()->bRequestedMoveUseAcceleration = false;
}

void AMushroom::BeginPlay() {
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AMushroom::OnHit);

	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMushroom::OnHit);

	setState(STATE_MUSHROOM::Start);
}

void AMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (this->state == STATE_MUSHROOM::Start) {
		AddMovementInput(FVector(0.0f, 0.0f, 1.0f), 5);
		if (this->GetTransform().GetLocation().Z > z) {
			setState(STATE_MUSHROOM::Run);
		}
	}
	else {
		AddMovementInput(FVector(direct, 0.0f, 0.0f), 1.5);

		UE_LOG(LogTemp, Warning, TEXT("%f"), GetCharacterMovement()->GravityScale);
	}

	
}

void AMushroom::setState(int s)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	FVector PlayerLocation;
	if (PlayerController != nullptr) {
		PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
	}

	switch (s)
	{
	case STATE_MUSHROOM::Start:
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		z = this->GetTransform().GetLocation().Z + 100.f;

		break;
	case STATE_MUSHROOM::Run:
		if (PlayerLocation.X > GetActorLocation().X) {
			direct = -1.0f;
		}
		
		GetCapsuleComponent()->SetCollisionProfileName(FName("Pawn"));
		//GetCharacterMovement()->SetGroundMovementMode(MOVE_Walking);
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
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

void AMushroom::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {

		mario->setLevel(MARIO_LEVEL_BIG);

		this->Destroy();
	}
}

void AMushroom::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {

		mario->setLevel(MARIO_LEVEL_BIG);

		this->Destroy();
	}
}

