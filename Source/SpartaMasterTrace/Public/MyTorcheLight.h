#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTorcheLight.generated.h"

UCLASS()
class SPARTAMASTERTRACE_API AMyTorcheLight : public AActor
{
	GENERATED_BODY()
	
public:
	AMyTorcheLight();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<TWeakObjectPtr<AActor>> Items;
};
