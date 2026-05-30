#include "MyObjectPool.h"
#include "PooledObject.h"

AMyObjectPool::AMyObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMyObjectPool::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;

	for (int32 PoolIndex = 0; PoolIndex < PooledObjectData.Num(); PoolIndex++)
	{
		FSingleObjectPool CurrentPoolIndex;

		SpawnParams.Name = FName(FString::Printf(TEXT("%s"), *PooledObjectData[PoolIndex].ActorName));

		SpawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;

		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int32 ObjectIndex = 0; ObjectIndex < PooledObjectData[PoolIndex].PoolSize; ObjectIndex++)
		{
			AActor* SpawnedActor = GetWorld()->SpawnActor(PooledObjectData[PoolIndex].ActorTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParams);

			SpawnedActor->SetActorLabel(SpawnedActor->GetName());

			UPooledObject* PoolComp = NewObject<UPooledObject>(SpawnedActor);

			PoolComp->RegisterComponent();

			SpawnedActor->AddInstanceComponent(PoolComp);

			PoolComp->Init(this);

			CurrentPoolIndex.PooledObjects.Add(PoolComp);

			SpawnedActor->SetActorHiddenInGame(true);
			SpawnedActor->SetActorEnableCollision(false);
			SpawnedActor->SetActorTickEnabled(false);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		}
		Pools.Add(CurrentPoolIndex);
	}

}

AActor* AMyObjectPool::GetPooledActor(FString Name)
{
	return nullptr;
}

void AMyObjectPool::RecycleActor(AActor* PooledActor)
{
}

void AMyObjectPool::RecyclePooledObject(UPooledObject* PoolCompRef)
{
}

void AMyObjectPool::Broadcast_PoolerCleanup()
{
}

void AMyObjectPool::RegenItem(int32 PoolIndex, int32 PositionIndex)
{
}



