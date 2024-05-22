// Fill out your copyright notice in the Description page of Project Settings.


#include "AmassonBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


AGameStateBase* UAmassonBlueprintFunctionLibrary::GetGameState(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetGameState(WorldContextObject);
}

AGameModeBase* UAmassonBlueprintFunctionLibrary::GetGameMode(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetGameMode(WorldContextObject);
}

UGameInstance* UAmassonBlueprintFunctionLibrary::GetGameInstance(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetGameInstance(WorldContextObject);
}

bool UAmassonBlueprintFunctionLibrary::RenameObject(UObject* Object, FString NewName, UObject* NewOuter)
{
    return Object->Rename(*NewName, NewOuter);
}
