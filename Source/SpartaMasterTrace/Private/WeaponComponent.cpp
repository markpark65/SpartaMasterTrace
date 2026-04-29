#include "WeaponComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
}


void UWeaponComponent::FireShotgun()
{
    AActor* Owner = GetOwner();
    ACharacter* Character = Cast<ACharacter>(Owner);
    if (!Owner || !Character) return;

    APlayerController* PC = Cast<APlayerController>(Character->GetController());

    FVector CameraLocation;
    FRotator CameraRotation;
    Character->GetActorEyesViewPoint(CameraLocation, CameraRotation);

    FVector MuzzleLocation = CameraLocation;
    FVector ShotDirection = CameraRotation.Vector();

    if (FireSound) UGameplayStatics::PlaySoundAtLocation(this, FireSound, Owner->GetActorLocation());
    if (MuzzleFlash) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, Owner->GetActorLocation());

    for (int32 i = 0; i < CurrentWeaponData.PelletCount; ++i)
    {
        FVector SpreadDir = GetSpreadDirection(ShotDirection);
        FVector EndLocation = MuzzleLocation + (SpreadDir * 5000.0f);

        FHitResult Hit;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(Owner);

        if (GetWorld()->LineTraceSingleByChannel(Hit, MuzzleLocation, EndLocation, ECC_Visibility, Params))
        {
            DrawDebugLine(GetWorld(), MuzzleLocation, Hit.ImpactPoint, FColor::Red, false, 1.0f, 0, 1.0f);
            if (ImpactEffect) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

            if (Hit.GetActor())
            {
                UGameplayStatics::ApplyDamage(Hit.GetActor(), 10.f, PC, Owner, nullptr);
            }
        }
        else
        {
            DrawDebugLine(GetWorld(), MuzzleLocation, EndLocation, FColor::Green, false, 1.0f, 0, 1.0f);
        }
    }

    ApplyRecoil();
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		UCameraComponent* Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();

		if (Camera)
		{
			WeaponMesh->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);

			WeaponMesh->SetRelativeLocation(FVector(40.f, 25.f, -10.f));
			WeaponMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		}
		else
		{
			WeaponMesh->SetupAttachment(OwnerCharacter->GetMesh());
		}
	}
}

FVector UWeaponComponent::GetSpreadDirection(FVector BaseDirection)
{
	float ConeHalfAngle = FMath::DegreesToRadians(CurrentWeaponData.SpreadAngle);
	return UKismetMathLibrary::RandomUnitVectorInConeInDegrees(BaseDirection, CurrentWeaponData.SpreadAngle);
}

void UWeaponComponent::ApplyRecoil()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character && Character->GetController())
	{
		APlayerController* PC = Cast<APlayerController>(Character->GetController());
		if (PC)
		{
			float RandomHorizontal = FMath::FRandRange(-CurrentWeaponData.HorizontalRecoil, CurrentWeaponData.HorizontalRecoil);

			PC->AddPitchInput(-CurrentWeaponData.VerticalRecoil);
			PC->AddYawInput(RandomHorizontal);
		}
	}
}