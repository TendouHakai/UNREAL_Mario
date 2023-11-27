// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

#include "BaseObject.h"

#include "PopupText.generated.h"

UCLASS()
class MARIO_API APopupText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APopupText();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* textComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int Number;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setNumber(int number);

};
