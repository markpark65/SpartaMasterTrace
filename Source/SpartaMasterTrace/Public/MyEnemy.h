#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemy.generated.h"

UCLASS()
class SPARTAMASTERTRACE_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AMyEnemy();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health = 100.f;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	void Die();

};
