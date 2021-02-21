// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

/*
 This game is like ahorcado, find the matching word
 If a letter is repeated and in the same position, is a bull
 If a letter is repeated but in different position, is a cow
*/

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    // One way to initialize structs:
    // FBullCowCount Count = {0,0};

    //GetValidWords: obtains an array full of isograms from an array full of words
    asRandomIsogram = GetValidWords(Words);

    InitGame();

    // PrintLine(TEXT("Valid words: %i"), Result.Num());
    // int32 IndexWords = 0;
    // while(IndexWords <= (Result.Num() - 1))
    // {
    //     PrintLine(TEXT("%s"), *Result[IndexWords]);
    //     IndexWords++;
    // }

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // If bGameOver is true, restart the game
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    //These are use for selecting a random word in the word list
    int32 iRandom = 0;

    iRandom = FMath::RandRange( 0 , (asRandomIsogram.Num() - 1) );

    //Set the a random hidden word and the length is the lives
    sHiddenWord  = asRandomIsogram[iRandom];
    iLives = sHiddenWord.Len();
    bGameOver = false;
    
    // Intro
    PrintLine(TEXT("Welcome tu Bull Cows Game!"));
    PrintLine(TEXT("Guess the %i letter word"), sHiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), iLives);
    PrintLine(TEXT("Type in your guess and press enter"));
    PrintLine(TEXT("The hidden word was: %s"), *sHiddenWord);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("Game Over. Press enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& sGuess)
{
    FBullCowCount Result;

    if (sGuess == sHiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You... WON!"));
        EndGame();
    }
    else
    {
        // Remove one life
        iLives--;
        PrintLine(TEXT("WRONG! Lives left: %i"),iLives);

        //Is the correct size?
        if (sHiddenWord.Len() != sGuess.Len())
        {
            // Remember size of the hidden word
            PrintLine(TEXT("Remember: the size of the word is %i"), sHiddenWord.Len());
        }
        else
        {
            //Isogram is a word with no repeating letters
            if(CheckIsogram(sGuess))
            {
                //If is an isogram, now lets check for repeated letters
                Result = GetBullCows(sGuess);
                PrintLine(TEXT("You have %i Bulls and %i Cows"), Result.iBulls, Result.iCows);
            }
            else
            {
                PrintLine(TEXT("No repeating characters, try again"));
            }
        }

        // failed the game if no more lives
        if(iLives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left"));
            PrintLine(TEXT("The hidden word was: %s"), *sHiddenWord);
            EndGame();
        }
        else{}
    }
}

// Returns true if is an isogram
bool UBullCowCartridge::CheckIsogram(const FString& sIsogram) const
{
    bool bCheck = true;
    int32 iFirstIndex = 0;
    int32 iSecondIndex = iFirstIndex + 1;

    while ( iFirstIndex <= (sIsogram.Len() -1) )
    {
        while( iSecondIndex <= (sIsogram.Len() -1) )
        {
            // Isogram is a word with no repeating letters
            if ( sIsogram[iFirstIndex] == sIsogram[iSecondIndex] )  
            {
                bCheck = false;
            }
            else{}
            iSecondIndex++;
        }
        iFirstIndex++;
        iSecondIndex = iFirstIndex + 1;
    }

    return bCheck;
}

// This function will get an array full of isograms from an array full of words
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& asWordList) const
{
    TArray<FString> ValidWords;

    // Range-Based For loop: Use it to avoid index in arrays
    for(FString WordIndex : asWordList)
    {
        if((WordIndex.Len() >= 4) && (WordIndex.Len() <= 8))
        {
            if(CheckIsogram(WordIndex))
            {
                //Add strings to the array
                ValidWords.Emplace(WordIndex);
            }
            else{}
        }
        else{}
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& sInput) const
{
    int32 iBullIndex = 0;
    int32 iCowIndex = 0;

    FBullCowCount Process;
    Process.iBulls = 0;
    Process.iCows = 0;

    // If a letter is repeated and in the same position, is a bull, if not is a cow
    while ( iBullIndex <= (sInput.Len() -1) )
    {
        // Repeated letter and the same position
        if( sInput[iBullIndex] == sHiddenWord[iBullIndex] )
        {
            Process.iBulls++;
        }
        else
        {
            while( iCowIndex <= (sInput.Len() -1) )
            {
                // Repeated letter but different position
                if ( sInput[iBullIndex] == sHiddenWord[iCowIndex] )  
                {
                    Process.iCows++;
                }
                else{}
                iCowIndex++;
            }
        }
        iBullIndex++;
        iCowIndex = 0;
    }

    return Process;
}