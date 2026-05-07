#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPARTAMASTERTRACE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();
	void Fire(); // 캐릭터가 호출할 함수

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeaponBase> WeaponClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class AWeaponBase* CurrentWeapon;
};