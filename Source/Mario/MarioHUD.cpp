// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioHUD.h"
#include "Widget/HUD_Widget.h"

AMarioHUD::AMarioHUD()
{
    coin = 0;
}

void AMarioHUD::BeginPlay()
{
    Super::BeginPlay();
    hudwidget = CreateWidget<UUserWidget>(GetWorld(), hudWidgetBP);

    if (hudwidget != nullptr) {
        hudwidget->AddToViewport();
    }
}

void AMarioHUD::addCoin(int c)
{
    UHUD_Widget* hudW = Cast<UHUD_Widget>(hudwidget);
    ++coin;

    if (hudW != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("update coin"));
        hudW->updateCoinText(coin);
    }
}
