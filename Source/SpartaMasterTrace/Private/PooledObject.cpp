#include "PooledObject.h"


void UPooledObject::Init(AMyObjectPool* Owner)
{
	bIsPoolActive = false;

	ObjectPool = Owner;
}

void UPooledObject::RecycleSelf()
{

}

void UPooledObject::OnComponentDestroyed(bool bDestroyingHierarchy)
{

}
