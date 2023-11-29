// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"

#include "Components/BoxComponent.h"

#include "GroundEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class MARIO_API AGroundEnemyBase : public AEnemyBase
{
	GENERATED_BODY()

protected:
	int direct;
public:
	AGroundEnemyBase();
	// ANIMATION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* GROUNDENEMY_WalkAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* GROUNDENEMY_DieAnimation;

	// BOX COLLIDER
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UpCollision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxComponent;

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void setState(int s) override;

	void Move();

	void TakeDamge();

	void Dead();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
		
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			const FHitResult& Hit);
};
