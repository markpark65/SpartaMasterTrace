#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS(Abstract)
class SPARTAMASTERTRACE_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	// 자식 무기들이 구현할 메인 발사 로직
	virtual void OnFire() PURE_VIRTUAL(AWeaponBase::OnFire, );

protected:
	// --- 샌드박스 함수들 (자식들이 가져다 씀) ---
	void ExecuteLineTrace(FHitResult& OutHit, float Distance, float SpreadAngle);
	void PlayEffects(const FHitResult& Hit);
	void ApplyRecoil(float Vertical, float Horizontal);

	// 공통 컴포넌트 및 효과 데이터[cite: 12, 16]
	UPROPERTY(VisibleAnywhere, Category = "Visual")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damage = 10.f;
};
