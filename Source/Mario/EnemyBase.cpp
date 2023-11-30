// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "MarioCharacter.h"

AEnemyBase::AEnemyBase() {
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxComponent->SetupAttachment(RootComponent);
	boxComponent->SetCollisionProfileName(FName("BlockAllDynamic"));

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentHit.AddDynamic(this, &AEnemyBase::OnHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnOverlapEnd);

	isDead = false;
	direct = 1.0f;
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	updateAnimation();
	Move();
}

void AEnemyBase::setState(int s)
{
	BaseObject::setState(s);
}

void AEnemyBase::Move()
{

}

int AEnemyBase::getDirect()
{
	return this->direct;
}

void AEnemyBase::setDirect(int d)
{
	this->direct = d;
	if (direct > 0) {
		SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else {
		SetActorRotation(FRotator(0.0, 180.0f, 0.0f));
	}
}

void AEnemyBase::takeDamage()
{

}

void AEnemyBase::Dead()
{
	UE_LOG(LogTemp, Warning, TEXT("Dead"));
	this->Destroy();
}

UPaperFlipbook* AEnemyBase::getAnimation()
{
	return nullptr;
}

void AEnemyBase::updateAnimation()
{
	UPaperFlipbook* animation = getAnimation();
	if (GetSprite()->GetFlipbook() != animation)
	{
		GetSprite()->SetFlipbook(animation);
	}
}

void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		mario->TakeDamage(1);
		boxComponent->SetCollisionProfileName(FName(TEXT("NoCollision")));
	}
}

void AEnemyBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		boxComponent->SetCollisionProfileName(FName(TEXT("BlockAllDynamic")));
	}
}

void AEnemyBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		mario->CauseDamage();
		takeDamage();
	}
}