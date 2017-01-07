/* 
	This is the console executable that makes use of the BullCow class
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class	
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//Function Prototype
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();


//Global Variables
FBullCowGame BCGame; // Instantiate a new game

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

//Print for introduction
void PrintIntro()
{
	// Introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";

	return; //Good habit in C++
}

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

	// TODO summarize game
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
		std::cout << "Try " << CurrentTry << ". Please enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
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
