// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTAMASTERTRACE_API UPooledObject : public UActorComponent
{
	GENERATED_BODY()

public:
	
	void Init(class UMyObjectPoolComponent* Owner);

	UFUNCTION(BlueprintCallable)
	void RecycleSelf();
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool bIsPoolActive;

private:
	TObjectPtr<class UMyObjectPoolComponent> ObjectPool;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
