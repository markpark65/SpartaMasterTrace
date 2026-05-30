#include "MyTorcheLight.h"
#include "TestMyInterface.h"
#include "Kismet/KismetSystemLibrary.h"

AMyTorcheLight::AMyTorcheLight()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyTorcheLight::BeginPlay()
{
	Super::BeginPlay();
	
	for (const TWeakObjectPtr<AActor>& Item : Items)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Item.Get(), UTestMyInterface::StaticClass()))
		{
			ITestMyInterface::Execute_OnFireDetected(Item.Get(), 100.f, FVector::ZeroVector);
		}
	}
}

void AMyTorcheLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

