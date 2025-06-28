// Amasson


#include "UI/WidgetControllerComponent.h"
#include "UI/WidgetController.h"


void UWidgetControllerComponent::BroadcastValues()
{
    BP_BroadcastValues();
}

void UWidgetControllerComponent::SetObservedActor(AActor* Actor)
{
    BP_SetObservedActor(Actor);
}

void UWidgetControllerComponent::BindCallbacksToDependencies()
{
    BP_BindCallbacksToDependencies();
}

UWidgetController* UWidgetControllerComponent::GetParentController() const
{
    if (!GetOuter())
        return nullptr;
    return Cast<UWidgetController>(GetOuter());
}
