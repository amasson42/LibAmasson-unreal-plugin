// Amasson


#include "UI/WidgetController.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Pawn.h"
#include "UI/WidgetControllerComponent.h"


UWidgetController::UWidgetController()
{

}

void UWidgetController::Construct()
{
    for (const auto& ComponentClass : ComponentsClass)
        AddComponentByClass(ComponentClass.Value, ComponentClass.Key);
}

UWidgetController* UWidgetController::MakeWidgetController(UObject* Outer, TSubclassOf<UWidgetController> WidgetControllerClass, AActor* ObservedActor)
{
    if (!IsValid(WidgetControllerClass))
        return nullptr;

    UWidgetController* NewWidgetController = NewObject<UWidgetController>(Outer, WidgetControllerClass);
    
    if (!IsValid(NewWidgetController))
        return nullptr;

    NewWidgetController->Construct();
    NewWidgetController->BP_Construct();

    if (IsValid(ObservedActor))
        NewWidgetController->SetObservedActor(ObservedActor, true);

    return NewWidgetController;
}

void UWidgetController::SetObservedController(AController* InController)
{
    if (!IsValid(InController)) return;

    Controller = InController;
    if (APlayerController* AsPC = Cast<APlayerController>(InController))
        PlayerState = AsPC->GetPlayerState<APlayerState>();
    else
        PlayerState = nullptr;
    Pawn = InController->GetPawn();
    Actor = InController;
}

void UWidgetController::SetObservedPlayerState(APlayerState* InPlayerState)
{
    if (!IsValid(InPlayerState)) return;

    Controller = InPlayerState->GetPlayerController();
    PlayerState = InPlayerState;
    Pawn = InPlayerState->GetPawn();
    Actor = InPlayerState;
}

void UWidgetController::SetObservedPawn(APawn* InPawn)
{
    if (!IsValid(InPawn)) return;

    Controller = InPawn->GetController();
    if (APlayerController* AsPC = Cast<APlayerController>(Controller))
        PlayerState = AsPC->GetPlayerState<APlayerState>();
    else
        PlayerState = nullptr;
    Pawn = InPawn;
    Actor = InPawn;
}

void UWidgetController::SetObservedActor(AActor* InActor, bool bTryCast)
{
    if (!IsValid(InActor)) return;

    if (bTryCast)
    {
        if (AController* AsPC = Cast<AController>(InActor))
            SetObservedController(AsPC);
        else if (APlayerState* AsPS = Cast<APlayerState>(InActor))
            SetObservedPlayerState(AsPS);
        else if (APawn* AsPawn = Cast<APawn>(InActor))
            SetObservedPawn(AsPawn);
    }
    else
    {
        Controller = nullptr;
        PlayerState = nullptr;
        Pawn = nullptr;
        Actor = InActor;
    }
    
    for (UWidgetControllerComponent* Wcc : Components)
    {
        if (IsValid(Wcc))
        {
            Wcc->SetObservedActor(InActor);
            Wcc->BP_SetObservedActor(InActor);
        }
    }

    ObservedActorSet();
    BP_ObservedActorSet();

    BindCallbacksToDependencies();
    BP_BindCallbacksToDependencies();
}

void UWidgetController::BroadcastValues()
{
    for (UWidgetControllerComponent* Component : Components)
    {
        Component->BroadcastValues();
    }
    BP_BroadcastValues();
}

void UWidgetController::BindCallbacksToDependencies()
{
    for (UWidgetControllerComponent* Component : Components)
    {
        Component->BindCallbacksToDependencies();
    }
}

void UWidgetController::BroadcastState(FName State)
{
    OnControllerStateUpdate.Broadcast(State);
}

UWidgetControllerComponent* UWidgetController::GetComponentByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass) const
{
    for (UWidgetControllerComponent* Component : Components)
    {
        if (Component->IsA(ComponentClass))
        {
            return Component;
        }
    }
    return nullptr;
}

UWidgetControllerComponent* UWidgetController::GetComponentByClassAndName(TSubclassOf<UWidgetControllerComponent> ComponentClass, FName ComponentName) const
{
    for (UWidgetControllerComponent* Component : Components)
    {
        if (Component->IsA(ComponentClass) && Component->GetFName() == ComponentName)
        {
            return Component;
        }
    }
    return nullptr;
}

TArray<UWidgetControllerComponent*> UWidgetController::GetComponentsByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass) const
{
    TArray<UWidgetControllerComponent*> ComponentsList;
    for (UWidgetControllerComponent* Component : Components)
    {
        if (Component->IsA(ComponentClass))
        {
            ComponentsList.Add(Component);
        }
    }
    return ComponentsList;
}

UWidgetControllerComponent* UWidgetController::AddComponentByClass(TSubclassOf<UWidgetControllerComponent> ComponentClass, FName ComponentName)
{
    UWidgetControllerComponent* NewComponent = NewObject<UWidgetControllerComponent>(this, ComponentClass, ComponentName);
    Components.Add(NewComponent);
    return NewComponent;
}
