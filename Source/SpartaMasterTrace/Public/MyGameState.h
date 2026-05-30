#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMonsterKilledSignature, AController*, Killer);

UCLASS()
class SPARTAMASTERTRACE_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMonsterKilledSignature OnMonsterKilledEvent;
};
