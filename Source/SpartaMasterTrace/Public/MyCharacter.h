#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WeaponComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class SPARTAMASTERTRACE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FirstPersonCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* MoveAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* LookAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* JumpAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* AttackAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* SprintAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* AimAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UWeaponComponent* WeaponComp;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartJump();
    void StopJump();

    void StartSprint();
    void StopSprint();

    void Attack();
    void StartAim();
    void StopAim();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // 시야각변수
    float DefaultFOV = 90.f; // 기본
    float AimFOV = 60.f;     // 조준 시
    float TargetFOV = 90.f;
};
