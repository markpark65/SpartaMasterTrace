#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponStruct.h"
#include "Shotgun.generated.h"

UCLASS()
class SPARTAMASTERTRACE_API AShotgun : public AWeaponBase
{
	GENERATED_BODY()
public:
	virtual void OnFire() override;

	UPROPERTY(EditAnywhere, Category = "Shotgun Stats")
	FShotgunData ShotgunData;
};