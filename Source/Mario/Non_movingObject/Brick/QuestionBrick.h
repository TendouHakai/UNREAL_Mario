// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Brick.h"

#include "QuestionBrick.generated.h"

/**
 * 
 */

// STATE
#define QUESTIONBRICK_STATE_START		1
#define QUESTIONBRICK_STATE_COLLECTED	2

// TYPE
enum TYPE_QUESTIONBRICK {
	Coin = 1,
	Mushroom = 2,
};

UCLASS()
class MARIO_API AQuestionBrick : public ABrick
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* hitComponent;

	//ANIMATION
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* QUESTIONBRICK_StartAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* QUESTIONBRICK_EndAnimation;

	UPROPERTY(EditAnyWhere, Category = Coin)
		TSubclassOf<AActor> coinObject;
	UPROPERTY(EditAnyWhere, Category = Mushroom)
		TSubclassOf<APawn> mushroomObject;
public:
	AQuestionBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = Type)
		int type;

private:
	float z;
	float startTime;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void setState(int s) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

};
