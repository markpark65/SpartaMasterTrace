#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
    GetCapsuleComponent()->InitCapsuleSize(40.f, 90.f);

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());

    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

    FirstPersonCamera->bUsePawnControlRotation = true;

    GetMesh()->SetupAttachment(FirstPersonCamera);
    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -150.f));

    GetCharacterMovement()->MaxWalkSpeed = 600.f;
    GetCharacterMovement()->JumpZVelocity = 500.f;
    GetCharacterMovement()->AirControl = 0.35f;

    WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::StartJump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);

        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMyCharacter::StartSprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMyCharacter::StopSprint);
    }
}
void AMyCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MoveVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MoveVector.Y);
        AddMovementInput(RightDirection, MoveVector.X);
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMyCharacter::StartJump() { Jump(); }
void AMyCharacter::StopJump() { StopJumping(); }

void AMyCharacter::StartSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void AMyCharacter::StopSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AMyCharacter::Attack()
{
    if (WeaponComp)
    {
        WeaponComp->FireShotgun();
    }
}