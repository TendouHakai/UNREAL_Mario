// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MARIO_API BaseObject
{
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		int state;
public:
	BaseObject();

	virtual void setState(int s) {
		if (this->state != s) {
			this->state = s;
		}
	}


	~BaseObject();
};
