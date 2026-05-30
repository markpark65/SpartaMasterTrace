#include "MyEnemy.h"
#include "MyGameState.h"
#include "DrawDebugHelpers.h"

AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

float AMyEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health -= ActualDamage;

    FVector DebugLocation = GetActorLocation() + FVector(0, 0, 100);
    FString HPString = FString::Printf(TEXT("HP: %.1f / 100"), Health);

    DrawDebugString(GetWorld(), FVector(0, 0, 100), HPString, this, FColor::Red, 2.0f);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,
            FString::Printf(TEXT("데미지 받음! 남은 HP: %.1f"), Health));
    }

    if (Health <= 0.f)
    {
        if (AMyGameState* GS = Cast<AMyGameState>(GetWorld()->GetGameState()))
        {
            GS->OnMonsterKilledEvent.Broadcast(EventInstigator);
        }

        Die();
    }
    return ActualDamage;
}

void AMyEnemy::Die()
{
	Destroy();
}