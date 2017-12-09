/*The game logic (no view code or direct user interaction)
The game is a simple guess word game based on Mastermind*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

//status after getting a user input after he's asked about the desired word length 
enum class EWordLengthInputStatus {
	Invalid_Status,
	Empty,
	Not_number,
	Out_of_bounds_number,
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); //empty constructor
	FBullCowGame(int32 WordLength); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	EWordLengthInputStatus CheckWordLengthValidity(FString) const;

	void Reset(int32);
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	FString HiddenWordAccordingToWordLength(int32) const;

	bool IsNumber(FString) const;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};