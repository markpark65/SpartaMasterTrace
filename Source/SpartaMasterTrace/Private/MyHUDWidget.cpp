#include "MyHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{

	if (HealthProgressBar && MaxHealth > 0.f)
	{

		float HealthPercentage = CurrentHealth / MaxHealth;
		HealthProgressBar->SetPercent(HealthPercentage);
	}
}

void UMyHUDWidget::UpdateQuest(int32 Current, int32 Target)
{
	if (QuestProgressText)
	{
		FString QuestString = FString::Printf(TEXT("몬스터 토벌: %d / %d"), Current, Target);
		QuestProgressText->SetText(FText::FromString(QuestString));
	}
}