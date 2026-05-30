#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyActorComponent.h"
#include "MyHUDWidget.h"
#include "MyQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TestMyInterface.h"
#include "ItemBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(40.f, 90.f);

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());

    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

    FirstPersonCamera->bUsePawnControlRotation = true;

    GetMesh()->SetupAttachment(GetCapsuleComponent());
    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -150.f));

    GetCharacterMovement()->MaxWalkSpeed = 600.f;
    GetCharacterMovement()->JumpZVelocity = 500.f;
    GetCharacterMovement()->AirControl = 0.35f;

    WeaponComp = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));
    HealthComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("HealthComponent"));
    QuestComponent = CreateDefaultSubobject<UMyQuestComponent>(TEXT("QuestComponent"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }

    if (HealthComponent)
    {
        HealthComponent->OnHealthDamaged.AddDynamic(this, &AMyCharacter::OnUpdateHealthUI);
        HealthComponent->OnHealthDead.AddDynamic(this, &AMyCharacter::OnPlayerDeath);
    }
    if (QuestComponent)
    {
        QuestComponent->OnQuestProgressUpdated.AddDynamic(this, &AMyCharacter::OnUpdateQuestUI);
    }
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
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AMyCharacter::StartAim);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AMyCharacter::StopAim);
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
        WeaponComp->Fire();
    }
}

void AMyCharacter::StartAim()
{
    TargetFOV = AimFOV;
}

void AMyCharacter::StopAim()
{
    TargetFOV = DefaultFOV;
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (FirstPersonCamera && FirstPersonCamera->FieldOfView != TargetFOV)
    {
        float NewFOV = FMath::FInterpTo(FirstPersonCamera->FieldOfView, TargetFOV, DeltaTime, 15.f);
        FirstPersonCamera->SetFieldOfView(NewFOV);
    }
}

void AMyCharacter::OnPlayerDeath(AController* InstigatorController)
{
    TArray<AActor*> AllItems;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemBase::StaticClass(), AllItems);

    for (AActor* ItemActor : AllItems)
    {
        if (ItemActor)
        {
            ItemActor->Destroy();
        }
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("플레이어 사망: 모든 아이템 제거됨"));
    }

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        DisableInput(PC);
    }

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
    GetMesh()->SetSimulatePhysics(true);

    // 무기가 있다면 무기도 떨어뜨리거나 숨기기
    if (WeaponComp)
    {
        WeaponComp->Deactivate();
    }
    //Destroy(); 
}

void AMyCharacter::OnUpdateHealthUI(float CurrentHealth, float MaxHealth, float HealthChange)
{
    UE_LOG(LogTemp, Warning, TEXT("UI 업데이트! 현재 체력: %f / %f"), CurrentHealth, MaxHealth);

    if (HUDWidget)
    {
        UMyHUDWidget* MyHUD = Cast<UMyHUDWidget>(HUDWidget);

        if (MyHUD)
        {
            MyHUD->UpdateHealth(CurrentHealth, MaxHealth);
        }
    }
}
void AMyCharacter::OnUpdateQuestUI(int32 Current, int32 Target)
{
    if (HUDWidget)
    {
        if (UMyHUDWidget* MyHUD = Cast<UMyHUDWidget>(HUDWidget))
        {
            MyHUD->UpdateQuest(Current, Target);
        }
    }
}