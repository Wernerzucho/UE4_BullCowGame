// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 iBulls = 0;
	int32 iCows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();
	void ProcessGuess(const FString& sGuess);
	bool CheckIsogram(const FString& sIsogram) const;
	TArray<FString> GetValidWords(const TArray<FString>& asWordList) const;
	FBullCowCount GetBullCows(const FString& sInput) const;


	// Your declarations go below!
	private:
	FString sHiddenWord;
	int32 iLives;
	bool bGameOver;
	TArray<FString> asRandomIsogram;
};
