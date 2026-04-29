#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WorldCollision.h"
#include "MyAIController.generated.h"

UCLASS()
class SPARTAMASTERTRACE_API AMyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	void StartDetection();

	void OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);

private:
	FTraceDelegate TraceDelegate;
	FTimerHandle DetectionTimerHandle;
};
