#include "MyQuestComponent.h"
#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"

UMyQuestComponent::UMyQuestComponent() 
{ 
	PrimaryComponentTick.bCanEverTick = false; 
}

void UMyQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AMyGameState* GS = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		GS->OnMonsterKilledEvent.AddDynamic(this, &UMyQuestComponent::HandleMonsterKilled);
	}
}

void UMyQuestComponent::HandleMonsterKilled(AController* Killer)
{

	if (CurrentKillCount < TargetKillCount)
	{
		CurrentKillCount++;
		OnQuestProgressUpdated.Broadcast(CurrentKillCount, TargetKillCount);

		if (CurrentKillCount >= TargetKillCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("퀘스트 달성! 100마리를 모두 처치했습니다."));
		}
	}
}

