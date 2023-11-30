// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"

#include "Components/BoxComponent.h"
#include "CheckFrontComponent.h"
#include "CheckFlatformComponent.h"

#include "GroundEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class MARIO_API AGroundEnemyBase : public AEnemyBase
{
	GENERATED_BODY()
public:
	AGroundEnemyBase();

	// BOX COLLIDER
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CheckfrontCollision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxCheckFrontComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CheckFlatformCollision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxCheckFlatformComponent;

	// CHECK FRONT COMPONENT
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = CheckfrontCollision, meta = (AllowPrivateAccess = "true"))
		UCheckFrontComponent* checkfrontComponent;

	// CHECK FLATFORM
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CheckflatformCollision, meta = (AllowPrivateAccess = "true"))
		UCheckFlatformComponent* checkPlatformComponent;
protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void setState(int s) override;

	// MOVE
	virtual void Move() override;

	virtual void takeDamage() override;

	virtual void Dead() override;

	virtual UPaperFlipbook* getAnimation();
};
