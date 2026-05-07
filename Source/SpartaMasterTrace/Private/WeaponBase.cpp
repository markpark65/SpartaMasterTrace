#include "WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponBase::ExecuteLineTrace(FHitResult& OutHit, float Distance, float SpreadAngle)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner) return;

	FVector CameraLoc; FRotator CameraRot;
	MyOwner->GetActorEyesViewPoint(CameraLoc, CameraRot);

	FVector ShotDir = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(CameraRot.Vector(), SpreadAngle);
	FVector End = CameraLoc + (ShotDir * Distance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(MyOwner);

	GetWorld()->LineTraceSingleByChannel(OutHit, CameraLoc, End, ECC_Visibility, Params);

	// 디버그 드로잉
	FVector MuzzleLoc = GetActorLocation();
	FVector DebugEnd = OutHit.bBlockingHit ? OutHit.ImpactPoint : End;
	DrawDebugLine(GetWorld(), MuzzleLoc, DebugEnd, OutHit.bBlockingHit ? FColor::Red : FColor::Green, false, 1.0f);
}

void AWeaponBase::PlayEffects(const FHitResult& Hit)
{
	if (FireSound) UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	if (MuzzleFlash) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, GetActorLocation());
	if (Hit.bBlockingHit && ImpactEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

void AWeaponBase::ApplyRecoil(float Vertical, float Horizontal)
{
	if (APawn* MyPawn = Cast<APawn>(GetOwner()))
		if (APlayerController* PC = Cast<APlayerController>(MyPawn->GetController()))
		{
			PC->AddPitchInput(-Vertical);
			PC->AddYawInput(FMath::FRandRange(-Horizontal, Horizontal));
		}
}