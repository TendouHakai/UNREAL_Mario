// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "../BaseObject.h"

#include "Mushroom.generated.h"

/**
 * 
 */

enum STATE_MUSHROOM {
	Start = 1,
	Run = 2,
	Collected = 3,
};

UCLASS()
class MARIO_API AMushroom : public APaperCharacter, public BaseObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	int z;
	int direct = 1.0f;
	
public:
	AMushroom();

	virtual void Tick(float DeltaTime) override;

	virtual void setState(int s) override;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, 
			FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
};
