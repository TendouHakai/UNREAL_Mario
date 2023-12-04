// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "../MarioCharacter.h"
#include "../MarioHUD.h"

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
	boxComponent->OnComponentHit.AddDynamic(this, &ACoin::OnHit);
	setState(STATE_COIN::START);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
}

void ACoin::setState(int s)
{
	APopupText* text = nullptr;

	switch (s)
	{
	case STATE_COIN::START:
		if (type == TYPE_COIN::GENERATE) {
			boxComponent->SetCollisionProfileName(FName("BlockAll"));
			boxComponent->SetSimulatePhysics(true);

			boxComponent->AddImpulse(FVector(0.f, 0.f, 700.f), NAME_None, true);
		}
		break;
	case STATE_COIN::COLLECTED:
		text = Cast<APopupText>(GetWorld()->SpawnActor<AActor>(textObject,
			this->GetTransform().GetLocation(), FRotator(0.f, 0.f, 0.f)));
		if (text != nullptr) {
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
	AMarioHUD* hud = Cast<AMarioHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (mario != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Collect coin"));
		if (hud != nullptr) {
			hud->addCoin(1);
		}
		setState(STATE_COIN::COLLECTED);
	}
}

void ACoin::OnHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	AMarioHUD* hud = Cast<AMarioHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	UE_LOG(LogTemp, Warning, TEXT("Collect coin 2"));
	if (hud != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Add coin"));
		hud->addCoin(1);
	}
	setState(STATE_COIN::COLLECTED);
}