/* 
	This is the console executable that makes use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class	
*/
#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// Function Prototype
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();


//Global Variables
FBullCowGame BCGame; // Instantiate a new game, which we re-use across play

int main()
{
	bool bPlayAgain = false;

	do{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);	

	return 0;
}

void PrintIntro()
{
	// Introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n\n";
	std::cout << "       /)   (\\ " << std::endl;	
	std::cout << "  .-._((,~\"~.))_.-,    ,-._~~,~""~.~~_.-,     " << std::endl;
	std::cout << "   `-.   e e   ,-'     `-.   o o   ,-'" << std::endl;
	std::cout << "     / ,o---o. \\         / ,o---o. \\" << std::endl;
	std::cout << "    ( ( .___. ) )   &   ( ( .___. ) )" << std::endl;
	std::cout << "     ) `-----' (         ) `-----' (" << std::endl;
	std::cout << "    /`-.__ __.-'\\       /`-.__ __.-'\\ " << std::endl;
	std::cout << "   /    BULLS    \\     /     COWS    \\ " << std::endl;
	std::cout << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";

	return; //Good habit in C++
}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset(); //Reset the values of the game
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); 
		
		// Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Please enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
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
	FText Response = "";
	std::cout << "Do you want to play again with the same hidden word (Y/N)? ";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You Won!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
