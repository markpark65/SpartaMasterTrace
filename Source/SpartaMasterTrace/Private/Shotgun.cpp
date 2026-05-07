#include "Shotgun.h"
#include "Kismet/GameplayStatics.h"

void AShotgun::OnFire()
{
	for (int32 i = 0; i < ShotgunData.PelletCount; ++i)
	{
		FHitResult Hit;
		ExecuteLineTrace(Hit, 5000.f, ShotgunData.SpreadAngle);

		if (Hit.GetActor())
		{
			UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, GetInstigatorController(), this, nullptr);
		}
		PlayEffects(Hit);
	}
	ApplyRecoil(ShotgunData.VerticalRecoil, ShotgunData.HorizontalRecoil);
}