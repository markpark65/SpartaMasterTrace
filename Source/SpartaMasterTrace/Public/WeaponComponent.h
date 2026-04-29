#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponStruct.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTAMASTERTRACE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireShotgun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Config")
	FShotgunData CurrentWeaponData;

protected:
	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystem* ImpactEffect;

	void ApplyRecoil();

	FVector GetSpreadDirection(FVector BaseDirection);

		
};
