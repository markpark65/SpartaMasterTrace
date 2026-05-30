#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "TestMyInterface.h"
#include "Item_Steel.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAMASTERTRACE_API AItem_Steel : public AItemBase, public ITestMyInterface
{
	GENERATED_BODY()

public:
	virtual void OnFireDetected_Implementation(float Temperature, FVector HitLocation) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<class UParticleSystem> FireEffect;
};
