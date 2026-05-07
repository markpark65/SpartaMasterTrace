#include "WeaponComponent.h"
#include "WeaponBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

UWeaponComponent::UWeaponComponent() { PrimaryComponentTick.bCanEverTick = false; }

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = GetOwner();
		Params.Instigator = Cast<APawn>(GetOwner());
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, Params);

		if (CurrentWeapon)
		{
			ACharacter* MyChar = Cast<ACharacter>(GetOwner());
			UCameraComponent* Cam = MyChar->FindComponentByClass<UCameraComponent>();
			CurrentWeapon->AttachToComponent(Cam, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			CurrentWeapon->SetActorRelativeLocation(FVector(40.f, 25.f, -10.f));
			CurrentWeapon->SetActorRelativeRotation(FRotator(0.f, -90.f, 0.f));
		}
	}
}

void UWeaponComponent::Fire()
{
	if (CurrentWeapon) CurrentWeapon->OnFire();
}