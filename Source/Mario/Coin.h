// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "BaseObject.h"
#include "PopupText.h"

#include "Coin.generated.h"

enum STATE_COIN {
	START=1,
	COLLECTED=2,
};

enum TYPE_COIN {
	NORMAL=1,
	GENERATE=2,
};

UCLASS()
class MARIO_API ACoin : public AActor, public BaseObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess = "true"))
		UPaperFlipbookComponent* flipbookComponent;

	UPROPERTY(EditAnyWhere, Category = PopUpText)
		TSubclassOf<AActor> textObject;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = Coin)
		int type;

	UPROPERTY(EditAnyWhere, Category = Coin)
		int coinNumber;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void setState(int s) override;

	// get set
	void setType(int t) {
		this->type = t;
		setState(STATE_COIN::START);
	}

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);
};
