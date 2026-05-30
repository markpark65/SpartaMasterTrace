#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class SPARTAMASTERTRACE_API UMyHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestProgressText;

	void UpdateQuest(int32 Current, int32 Target);
	void UpdateHealth(float CurrentHealth, float MaxHealth);
};
