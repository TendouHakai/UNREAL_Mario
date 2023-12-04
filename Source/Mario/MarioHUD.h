// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MarioHUD.generated.h"

/**
 * 
 */
UCLASS()
class MARIO_API AMarioHUD : public AHUD
{
	GENERATED_BODY()

protected:
	int NumberPlay;
	int coin;
	int Time;

	UUserWidget* hudwidget;

	UPROPERTY(EditAnyWhere, Category = HUD)
		TSubclassOf<UUserWidget> hudWidgetBP;
public:
	AMarioHUD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void addCoin(int c);
};
