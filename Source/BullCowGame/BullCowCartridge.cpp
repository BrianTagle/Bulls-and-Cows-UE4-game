// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the game!\nPress Tab to access the console..."));
    PrintLine(TEXT("To enter a guess, type your guess and press enter"));
    InitGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
    else //process the guess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
   
    bGameOver = false;
    HiddenWord = Isograms[FMath::RandRange(0, (Isograms.Num()-1))];
    //const TCHAR HW[] = TEXT("hunter");
    Lives = HiddenWord.Len();
    PrintLine(FString::Printf(TEXT("Can you guess the %i character long word?"), HiddenWord.Len()));
    PrintLine(FString::Printf(TEXT("You have %i Lives"), Lives));
    
    //PrintLine(FString::Printf(TEXT("The hidden word is %i characters long"), HiddenWord.Len() ));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(FString::Printf(TEXT("The hidden word was %s"), *HiddenWord));
    PrintLine(TEXT("Press Enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
    }
    else
    {
        
        if (Lives > 0)
        {
            if (Guess.Len() == HiddenWord.Len())
            {
                if (IsIsogram(Guess))
                {
                --Lives;
                PrintLine(FString::Printf(TEXT("Sorry, try guessing again! \n you have %i Lives remaning"), Lives));
                FindBullsAndCows(Guess);
                PrintLine(FString::Printf(TEXT("Bulls: %i, Cows: %i"), Bulls, Cows));
                }
                else
                {
                    PrintLine(TEXT("Sorry, your guess is not an isogram\ntry again"));
                }
                
                


            }
            else //wrong word length
            {
                PrintLine(FString::Printf(TEXT("Sorry, your guess has the wrong number of characters. \nThe hidden word has %i characters"), HiddenWord.Len()));
                return;
            }
            
        }
        else
        {
            PrintLine(TEXT("You ran out of lives and lost!"));
            EndGame();
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString &Guess) const
{
    for(size_t i = 0; i < Guess.Len(); i++)
    {
        for (size_t j = 0; j < Guess.Len(); j++)
        {
           if ( (i != j) && (Guess[i] == Guess[j]))
           {
               return false;
           }
           
        }
        
    }
    return true;
}

void UBullCowCartridge::FindBullsAndCows(const FString &Guess)
{
    Bulls = 0;
    Cows = 0;
    for(size_t i = 0; i < Guess.Len(); i++)
    {
        for (size_t j = 0; j < HiddenWord.Len(); j++)
        {
           if ( (i == j) && (Guess[i] == HiddenWord[j]))
           {
               Bulls++;
           }
           else if (Guess[i] == HiddenWord[j])
           {
               Cows++;
           }
           
        }
        
    }
    return;
}