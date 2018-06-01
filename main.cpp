/*
  main.cpp
  BullCowGame

 This is the console executable, which makes use of the BullCow class.
 This acts as the *V*iew in the MVC pattern, and is responsible for all user-interaction.
 For game logic, see FBullCowGame class.
 
 
  Created by Robert Prince on 10/19/17.
  Copyright © 2017 Robert Prince. All rights reserved.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"


// makes syntax Unreal-friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // INSTANTIATE a new game

// START
int main()
{
    
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while(true);
    
   
    return 0;
}


// introduce the game
void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game by Robert Prince.\n";
    std::cout << std::endl;
    std::cout << "          }    {           ___ " << std::endl;
    std::cout << "          (o  o)          (o o)" << std::endl;
    std::cout << "   /-------\\  /            \\ /--------\\ " << std::endl;
    std::cout << "  / | BULL |O               O| COW   | \\" << std::endl;
    std::cout << " *  |-,--- |                 | ----- |  *" << std::endl;
    std::cout << "    ^      ^                 ^       ^" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}


// track how many guesses the user has made
void PlayGame()
{

    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    
    //std::cout << MaxTries << std::endl;
    
    // loop asking for guesses while
    // the game is NOT won & until there are still tries remaining
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        
        // submit valid guess to the game and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

    }
    
    PrintGameSummary();
    return;
}


// loop continually until user provides a valid guess
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        // get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin,Guess);
        
        // check status and give feedback
        Status  = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << "-letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please use lowercase letters only.\n\n";
                break;
            default:
                // assume the guess is valid
                break;
        }
    } while (Status != EGuessStatus::OK); // keep looping until we get valid input
    return Guess;
}


bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else {
        std::cout << "Better luck next time!\n";
    }
    return;
}

