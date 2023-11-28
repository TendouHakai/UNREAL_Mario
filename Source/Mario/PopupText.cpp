// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupText.h"

// Sets default values
APopupText::APopupText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxComponent->SetupAttachment(RootComponent);
	boxComponent->SetSimulatePhysics(false);
	
	//boxComponent->SetCollisionProfileName(FName("NoCollision"));

	// create textrendercomponent
	textComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	textComponent->SetupAttachment(boxComponent);

	Number = 0;
}

// Called when the game starts or when spawned
void APopupText::BeginPlay()
{
	Super::BeginPlay();
	
	boxComponent->SetSimulatePhysics(true);
	boxComponent->AddImpulse(FVector(0.f, 0.f, 800.f), NAME_None, true);

	textComponent->SetText(FString::FromInt(Number));
	
}

// Called every frame
void APopupText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->GetVelocity().Z < 0.f) {
		this->Destroy();
	}
}

void APopupText::setNumber(int number)
{
	if (number > 0) {
		Number = number;

		textComponent->SetText(FString::FromInt(Number));
	}
}

