// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

AEnemyBase::AEnemyBase() {
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Move();
}

void AEnemyBase::setState(int s)
{
	BaseObject::setState(s);
}

void AEnemyBase::Move()
{
}

void AEnemyBase::TakeDamge()
{

}

void AEnemyBase::Dead()
{
	this->Destroy();
}
