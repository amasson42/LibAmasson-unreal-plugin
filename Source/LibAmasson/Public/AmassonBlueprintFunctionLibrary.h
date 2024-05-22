// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AmassonBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LIBAMASSON_API UAmassonBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game")
	static AGameStateBase* GetGameState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game")
	static AGameModeBase* GetGameMode(const UObject* WorldContextObject);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game")
	static UGameInstance* GetGameInstance(const UObject* WorldContextObject);


    UFUNCTION(BlueprintCallable)
    static bool RenameObject(UObject* Object, FString NewName, UObject* NewOuter);

};
