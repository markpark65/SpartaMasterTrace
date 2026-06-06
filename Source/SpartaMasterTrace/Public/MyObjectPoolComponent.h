#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledObjectData.h"
#include "MyObjectPoolComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolerCleanupSignature);

USTRUCT(BlueprintType)
struct FSingleObjectPool
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<class UPooledObject>> PooledObjects;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTAMASTERTRACE_API UMyObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyObjectPoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
    UPROPERTY()
    FPoolerCleanupSignature OnPoolerCleanup;

    UFUNCTION(BlueprintCallable)
    AActor* GetPooledActor(FString Name);

    UFUNCTION(BlueprintCallable)
    void RecycleActor(AActor* PooledActor);

    UFUNCTION(BlueprintCallable)
    void RecyclePooledObject(class UPooledObject* PoolCompRef);

    UFUNCTION(BlueprintCallable)
    void Broadcast_PoolerCleanup();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pool Settings")
    TArray<FPooledObjectData> PooledObjectData;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pool Settings")
    TArray<FSingleObjectPool> Pools;

private:
    void RegenItem(int32 PoolIndex, int32 PositionIndex);

		
};
