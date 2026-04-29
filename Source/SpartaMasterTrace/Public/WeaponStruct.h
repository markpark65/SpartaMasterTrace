#pragma once

#include "CoreMinimal.h"
#include "WeaponStruct.generated.h"

USTRUCT(BlueprintType)
struct FShotgunData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Stats")
    int32 PelletCount = 8;

    UPROPERTY(EditAnywhere, Category = "Stats")
    float SpreadAngle = 5.0f;

    UPROPERTY(EditAnywhere, Category = "Recoil")
    float VerticalRecoil = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Recoil")
    float HorizontalRecoil = 0.5f;
};