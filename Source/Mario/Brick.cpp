// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create UboxComponent
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxComponent->SetupAttachment(RootComponent);
	boxComponent->SetCollisionProfileName(FName("BlockAll"));

	// create Uflipbook
	flipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	flipbookComponent->SetupAttachment(boxComponent);
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::setState(int s)
{
	BaseObject::setState(s);
}

