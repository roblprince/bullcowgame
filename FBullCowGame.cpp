//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Robert Prince on 11/25/17.
//  Copyright © 2017 Robert Prince. All rights reserved.
//

#pragma once

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using int32 = int;



FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 5}, {5, 5}, {6, 12}, {7, 12}, {8, 15} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}



void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "distance";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess) /*false*/) // if if the guess isn't all lowercase,
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong,
    {
        return EGuessStatus::Wrong_Length;
    }
    else // otherwise
    {
        return EGuessStatus::OK;
    }
}

// PURPOSE: receives VALID guesses, increments turns, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    //----- Breakdown of Function ------
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();
    
    // loop through all letters in the hidden word (a for loop, then a conditional statement)
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
        for (int32 GChar = 0; GChar < WordLength; GChar++) {
            //    ^ compare letters to guess
            if (Guess[GChar] == MyHiddenWord[MHWChar]) { // if they match then
                if (MHWChar == GChar) { //if they're in the same place then
                    BullCowCount.Bulls++; // increment bulls
                }
                else {   //else
                    BullCowCount.Cows++; //increment cows
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength){
        bGameIsWon = true;
    }
    else {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    
    for (auto Letter : Word) // for all letters of the word
    {
        Letter = tolower(Letter); // to handle mixed-case words
        if(LetterSeen[Letter]) { return false; } // if letter is in map, we do NOT have isogram
        else { LetterSeen[Letter] = true; } // add the letter to the map as seen
    }

    
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter: Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    
    return true;
}
