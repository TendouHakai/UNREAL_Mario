// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundEnemyBase.h"
#include "MarioCharacter.h"
#include "Components/CapsuleComponent.h"


AGroundEnemyBase::AGroundEnemyBase()
{
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxComponent->SetupAttachment(RootComponent);
}

void AGroundEnemyBase::BeginPlay() {
	Super::BeginPlay();

	boxComponent->OnComponentHit.AddDynamic(this, &AGroundEnemyBase::OnHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGroundEnemyBase::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AGroundEnemyBase::OnOverlapEnd);



	isDead = false;
	direct = 1.0f;
}

void AGroundEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Move();
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

void AGroundEnemyBase::TakeDamge()
{

}

void AGroundEnemyBase::Dead()
{
	Super::Dead();
}

void AGroundEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario!= nullptr) {
		boxComponent->SetCollisionProfileName(FName(TEXT("NoCollision")));
	}
}

void AGroundEnemyBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		boxComponent->SetCollisionProfileName(FName(TEXT("BlockAllDynamic")));
	}
}

void AGroundEnemyBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		mario->CauseDamage();

		this->Destroy();
	}
}
