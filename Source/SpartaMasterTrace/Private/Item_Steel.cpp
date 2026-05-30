#include "Item_Steel.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
void AItem_Steel::OnFireDetected_Implementation(float Temperature, FVector HitLocation)
{
	if (FireEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			FireEffect,
			GetActorLocation(),
			GetActorRotation(),
			FVector(1.f)
		);
	}
}
