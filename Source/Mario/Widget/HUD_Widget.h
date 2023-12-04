// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "HUD_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MARIO_API UHUD_Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* NumberPlayText;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* TimeText;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* CoinText;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* PointText;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
        UTextBlock* WorldText;
public:
    void updateCoinText(int coin) {
        UE_LOG(LogTemp, Warning, TEXT("Coin UI"));
        CoinText->SetText(FText::AsNumber(coin));
    }
};
