#include "PooledObject.h"
#include "MyObjectPoolComponent.h"

void UPooledObject::Init(UMyObjectPoolComponent* Owner)
{
	bIsPoolActive = false;
	ObjectPool = Owner;
}

void UPooledObject::RecycleSelf()
{
	ObjectPool->RecyclePooledObject(this);
}

void UPooledObject::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	ObjectPool->OnPoolerCleanup.RemoveDynamic(this, &UPooledObject::RecycleSelf);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
