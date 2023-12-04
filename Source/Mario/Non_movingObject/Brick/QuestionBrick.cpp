// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestionBrick.h"
#include "../../MarioCharacter.h"
#include "../Coin.h"

AQuestionBrick::AQuestionBrick() {

	//create hit component
	hitComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollsion"));
	hitComponent->SetupAttachment(boxComponent);
	hitComponent->SetCollisionProfileName(FName("OverlapAll"));
}

void AQuestionBrick::BeginPlay()
{
	Super::BeginPlay();
	
	hitComponent->OnComponentBeginOverlap.AddDynamic(this, &AQuestionBrick::OnOverlapBegin);
	setState(QUESTIONBRICK_STATE_START);
}

void AQuestionBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (startTime >= 0.1f) {
		if (state == QUESTIONBRICK_STATE_COLLECTED) {
			FTransform tranform = this->GetTransform();
			FVector loca = tranform.GetLocation();

			if (this->GetActorLocation().Z <= z) {
				boxComponent->SetSimulatePhysics(false);
				loca.Z = z;
				tranform.SetLocation(loca);
			}
		}
	}
	else startTime += DeltaTime;
}

void AQuestionBrick::setState(int s)
{
	if (this->state == s) return;

	ACoin* object = nullptr;

	FVector location = this->GetTransform().GetLocation();
	
	switch (s)
	{
	case QUESTIONBRICK_STATE_START:
		boxComponent->SetSimulatePhysics(false);
		z = this->GetActorTransform().GetLocation().Z;
		break;
	case QUESTIONBRICK_STATE_COLLECTED:
		if (type == TYPE_QUESTIONBRICK::Coin) {
			location.Z += 50.f;
			object = Cast<ACoin>(GetWorld()->SpawnActor<AActor>(coinObject, location, FRotator(0.f, 0.f, 0.f)));
			if (object != nullptr) {
				object->setType(TYPE_COIN::GENERATE);
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Spawn mushroom"));
			GetWorld()->SpawnActor<ACharacter>(mushroomObject, location, FRotator(0.f, 0.f, 0.f));
		}


		boxComponent->SetSimulatePhysics(true);
		boxComponent->AddImpulse(FVector(0.f, 0.f, 350.f), NAME_None, true);
		startTime = 0.f;

		flipbookComponent->SetFlipbook(QUESTIONBRICK_EndAnimation);
		break;
	default:
		break;
	}


	ABrick::setState(s);
}

void AQuestionBrick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMarioCharacter* mario = Cast<AMarioCharacter>(OtherActor);
	if (mario != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Mario Collision with question Brick"));
		setState(QUESTIONBRICK_STATE_COLLECTED);
	}
}
