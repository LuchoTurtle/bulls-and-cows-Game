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
FText GetGuess();

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
	//change from FOR to WHILE loop once we are validating tries
	constexpr int32 NUMBER_OF_TURNS = 5;

	for (int32 i = 0; i < NUMBER_OF_TURNS; i++) {
		FText Guess = GetGuess(); //TODO make check for valid guesses

		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		//Print number of bulls and cows
		std::cout << "Bulls = "  << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl ;

		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}

	//TODO add a game summary

}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

FText GetGuess() {

	std::cout << "Try " << BCGame.GetCurrentTry() << std::endl;
	
	//get a guess from the player
	FText Guess = "";
	std::cout << "Enter your guess: ";
	std::getline(std::cin, Guess);	

	return Guess;
}