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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UWeaponComponent* WeaponComp;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartJump();
    void StopJump();

    void StartSprint();
    void StopSprint();

    void Attack();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
