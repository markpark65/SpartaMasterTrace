#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"

AMyPlayerController::AMyPlayerController()
    : DefaultMappingContext(nullptr)
    , MoveAction(nullptr)
    , JumpAction(nullptr)
    , LookAction(nullptr)
    , SprintAction(nullptr)
    , AttackAction(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }

    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());
}