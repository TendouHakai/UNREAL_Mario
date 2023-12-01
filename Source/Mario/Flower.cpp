// Fill out your copyright notice in the Description page of Project Settings.


#include "Flower.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BulletBase.h"
#include "MarioCharacter.h"

AFlower::AFlower()
{
	GetCharacterMovement()->MovementMode = MOVE_Flying;
	GetCharacterMovement()->GravityScale = 0.f;

	boxCheckIsInRangeComponent = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("checkIsInRange"));
	boxCheckIsInRangeComponent->SetupAttachment(RootComponent);

	shootPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootPosition"));
	shootPosition->SetupAttachment(RootComponent);
}

void AFlower::BeginPlay()
{
	Super::BeginPlay();

	boxCheckIsInRangeComponent->OnComponentBeginOverlap.AddDynamic(this, &AFlower::OnOverlapBeginCheckPlayer);
	boxCheckIsInRangeComponent->OnComponentEndOverlap.AddDynamic(this, &AFlower::OnOverlapEndCheckPlayer);

	startLocation = this->GetActorLocation();
	isInRange = false;
}

void AFlower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFlower::setState(int s)
{
	if (state == s) return;

	switch (s)
	{
	case STATE_RED_FLOWER::Idle:
		break;
	case STATE_RED_FLOWER::Fire:
		Fire();
		break;
	default:
		break;
	}

	Super::setState(s);
}

void AFlower::Fire()
{
	if (!isInRange) return;
	ABulletBase*  bullet = Cast<ABulletBase>(
		GetWorld()->SpawnActor<AActor>(bulletObject, shootPosition->GetComponentLocation(), FRotator(0.f, 0.f, 180.f))
		);

	FVector d = shootPosition->GetForwardVector();
	if (bullet != nullptr) {
		if (marioPosition.Z > this->GetActorLocation().Z)
			d.Z = -0.5f;
		else d.Z = 0.5f;

		bullet->setDirect(d);
	}
}

void AFlower::Move()
{
	marioPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (marioPosition.X > this->GetActorLocation().X) {
		this->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
	else {
		this->SetActorRotation(FRotator(0.f, 180.f, 0.f));
	}
}

UPaperFlipbook* AFlower::getAnimation()
{
	UPaperFlipbook* ani = nullptr;
	if (state == STATE_RED_FLOWER::Idle)
		ani = IDLE_Animation;
	else {
		if (GetSprite()->GetFlipbook() == IDLE_Animation) {
			if (marioPosition.Z > this->GetActorLocation().Z)
				ani = UP_FIRE_Animation;
			else ani = DOWN_FIRE_Animation;
		}
		else ani = GetSprite()->GetFlipbook();
	}
	return ani;
}

void AFlower::UpdateTimeLine(float value)
{
	FVector location = startLocation;
	location.Z += Distance * value;

	if (value>=1) setState(STATE_RED_FLOWER::Fire);
	else setState(STATE_RED_FLOWER::Idle);

	this->SetActorLocation(location);
}

void AFlower::OnOverlapBeginCheckPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		this->isInRange = true;
	}
}

void AFlower::OnOverlapEndCheckPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		this->isInRange = false;
	}
}
