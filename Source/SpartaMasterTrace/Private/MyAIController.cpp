#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "DrawDebugHelpers.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	TraceDelegate.BindUObject(this, &AMyAIController::OnTraceCompleted);
	GetWorldTimerManager().SetTimer(DetectionTimerHandle, this, &AMyAIController::StartDetection, 0.5f, true);
}

void AMyAIController::StartDetection()
{
	APawn* ControlledPawn = GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!ControlledPawn || !PlayerPawn) return;

	FVector Start = ControlledPawn->GetActorLocation();
	FVector End = PlayerPawn->GetActorLocation();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(ControlledPawn);
	Params.AddIgnoredActor(GetPawn());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.4f, FColor::Yellow, TEXT("비동기 Trace 시도 중..."));
	}

	GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Single,
		Start, End,
		ECC_Visibility,
		Params,
		FCollisionResponseParams::DefaultResponseParam,
		&TraceDelegate
	);
}

void AMyAIController::OnTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, TEXT("비동기 결과 수신 완료"));

    if (Data.OutHits.Num() > 0)
    {
        AActor* HitActor = Data.OutHits[0].GetActor();
        if (!HitActor) return;

        APawn* HitPawn = Cast<APawn>(HitActor);

        if (HitPawn && HitPawn->IsPlayerControlled())
        {
            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("플레이어 발견! 추격 시작"));

            UPathFollowingComponent* Pather = GetPathFollowingComponent();
            if (Pather && Pather->GetStatus() != EPathFollowingStatus::Moving)
            {
                EPathFollowingRequestResult::Type MoveResult = MoveToActor(HitPawn, 500.0f);

                if (MoveResult == EPathFollowingRequestResult::Failed && GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("경로 찾기 실패 (NavMesh 확인 필요)"));
                }
            }
        }
        else
        {
            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.4f, FColor::Orange,
                FString::Printf(TEXT("시야 가림: %s"), *HitActor->GetName()));
        }
    }
}