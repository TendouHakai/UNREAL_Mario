// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "MarioCharacter.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxComponent->SetupAttachment(RootComponent);

	// create Uflipbook
	flipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	flipbookComponent->SetupAttachment(boxComponent);

	type = TYPE_COIN::NORMAL;
	coinNumber = 100;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	AActor::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);


}

void ACoin::setState(int s)
{
	if (this->state == s) return;

	APopupText* text = nullptr;

	switch (s)
	{
	case STATE_COIN::START:
		break;
	case STATE_COIN::COLLECTED:
		text = Cast<APopupText>(GetWorld()->SpawnActor<AActor>(textObject,
			this->GetTransform().GetLocation(), FRotator(0.f, 0.f, 0.f)));
		if (text != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("run"));
			text->setNumber(coinNumber);
		}
		this->Destroy();
		break;
	default:
		break;
	}

	BaseObject::setState(s);
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);

	if (mario != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Collect coin"));

		setState(STATE_COIN::COLLECTED);
	}
}

