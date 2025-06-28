// Amasson


#include "UI/WidgetControllerComponents/GameManagementWcc.h"
#include "Kismet/GameplayStatics.h"


void UGameManagementWcc::SetObservedActor(AActor* Actor)
{
    WorldContextObject = Actor;
}


/** GameplayStatics */

void UGameManagementWcc::OpenLevel(FName LevelName, bool bAbsolute, FString Options)
{
    UGameplayStatics::OpenLevel(WorldContextObject, LevelName, bAbsolute, Options);
}

void UGameManagementWcc::OpenLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld> Level, bool bAbsolute, FString Options)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(WorldContextObject, Level, bAbsolute, Options);
}
