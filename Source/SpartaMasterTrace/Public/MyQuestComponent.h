// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyQuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestProgressSignature, int32, Current, int32, Target);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTAMASTERTRACE_API UMyQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMyQuestComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int32 TargetKillCount = 100; // 목표치 (100마리)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	int32 CurrentKillCount = 0;  // 현재치

	UPROPERTY(BlueprintAssignable)
	FOnQuestProgressSignature OnQuestProgressUpdated;

protected:
	virtual void BeginPlay() override;

	// 알림판(GameState)에서 방송이 울리면 실행될 함수
	UFUNCTION()
	void HandleMonsterKilled(AController* Killer);

		
};
