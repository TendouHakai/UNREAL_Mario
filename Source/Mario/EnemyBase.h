// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "BaseObject.h"
#include "PopupText.h"
#include "Components/BoxComponent.h"

#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class MARIO_API AEnemyBase : public APaperCharacter, public BaseObject
{
	GENERATED_BODY()

protected:
	//PROPERTY
	float Speed;
	int coin;
	bool isDead = false;
	int direct;

public:
	AEnemyBase();
	UPROPERTY(EditAnyWhere, Category = PopUpText)
		TSubclassOf<AActor> textObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UpCollision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxComponent;

	// ANIMATION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IDLE_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DIE_Animation;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void setState(int s) override;

	virtual void Move();
	virtual int getDirect();
	virtual void setDirect(int d);

	virtual void takeDamage();

	virtual void Dead();

	virtual UPaperFlipbook* getAnimation();
	virtual void updateAnimation();

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
