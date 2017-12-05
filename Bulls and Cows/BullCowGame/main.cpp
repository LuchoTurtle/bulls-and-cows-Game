/*
This is the console executable that makes use of the BullCowClass.
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic, see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame;	//instantiate a new game

//the entry point for our application
int main() {
	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}



void PrintIntro() {
	//Introduce the game
	std::cout << "Welcome to Bulls and Cows, lads\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";

	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of turns asking for guesses
	for (int32 i = 0; i < MaxTries; i++) {	//TODO change from FOR to WHILE loop once we are validating tries
		FText Guess = GetValidGuess(); 

		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls = "  << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";

	}

	//TODO add a game summary

}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

//loop continually until the user gives valid input
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << "\n";

		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

	 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get a valid input
	return Guess;

}