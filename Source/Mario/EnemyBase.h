// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "BaseObject.h"
#include "PopupText.h"

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

public:
	AEnemyBase();
	UPROPERTY(EditAnyWhere, Category = PopUpText)
		TSubclassOf<AActor> textObject;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void setState(int s) override;

	void Move();

	void TakeDamge();

	void Dead();
};
