// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "Components/ArrowComponent.h"

#include "Flower.generated.h"

/**
 * 
 */

enum STATE_RED_FLOWER {
	Idle = 1,
	Fire = 2,
};

UCLASS()
class MARIO_API AFlower : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Range)
		float Distance;

	FVector marioPosition;
	bool isInRange;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Range)
		FVector startLocation;

	// RANGE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CheckIsInRange, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxCheckIsInRangeComponent;

	// ANIMATION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* UP_FIRE_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DOWN_FIRE_Animation;

	// BULLET
	UPROPERTY(EditAnyWhere, Category = Bullet)
		TSubclassOf<AActor> bulletObject;

	// SHOOT POSITION
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bullet, meta = (AllowPrivateAccess = "true"))
		UArrowComponent* shootPosition;

public:
	AFlower();
	virtual void Tick(float DeltaSeconds) override;

	virtual void setState(int s) override;
	void Fire();

	virtual void Move();
	virtual UPaperFlipbook* getAnimation();

	UFUNCTION(BlueprintCallable, Category = "Timeline")
		void UpdateTimeLine(float value);

	UFUNCTION()
		void OnOverlapBeginCheckPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEndCheckPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
