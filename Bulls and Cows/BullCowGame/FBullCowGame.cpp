#pragma once

#include "FBullCowGame.h"
#include <map>

//to make syntax Unreal friendly
#define TMap std::map 
#define DEFAULT_WORD_LENGTH 3

//empty constructor
FBullCowGame::FBullCowGame() {
	Reset(DEFAULT_WORD_LENGTH);
}

//constructor
FBullCowGame::FBullCowGame(int32 WordLength) {
	Reset(WordLength);
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon;}

//difficulty and play tuning, the bigger the word length, the bigger the max tries
int32 FBullCowGame::GetMaxTries() const { 

	TMap<int32, int32> WordLengthToMaxTries{
		{3,4},
		{4,7},
		{5,10},
		{6,16},
		{7,20},
	};
	
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset(int32 Length) {

	MyHiddenWord = HiddenWordAccordingToWordLength(Length);
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//the hidden word is different according to the user's desired word length
FString FBullCowGame::HiddenWordAccordingToWordLength(int32 Length) const {

	TMap<int32, FString> WordToWordLength{
	{ 3,"ant" },
	{ 4, "mate" },
	{ 5, "plane" },
	{ 6, "planet" },
	{ 7, "isogram" },
	};

	return WordToWordLength[Length];
}

bool FBullCowGame::IsNumber(FString String) const {

	try {
		std::stoi(String);
	}
	catch (std::invalid_argument e) {
		return false;
	}
	
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {

	if (!IsIsogram(Guess)) {	//if the guess isn't an isogram, 
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowerCase(Guess)) {	//if the guess isn't all lowercase 
		return EGuessStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != Guess.length()) {	//if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}

}

//checks if user's input after he's asked for desired word length is valid
EWordLengthInputStatus FBullCowGame::CheckWordLengthValidity(FString String) const {

	if (String.empty()) {
		return EWordLengthInputStatus::Empty;
	}
	else if (!IsNumber(String)) {
		return EWordLengthInputStatus::Not_number;
	}
	else {
		//if it arrives here, it's because it's a number 
		int32 Length = std::stoi(String);
		if (Length < 3 || Length > 7) {
			return EWordLengthInputStatus::Out_of_bounds_number;
		}
	}

	return EWordLengthInputStatus::OK;
}

//receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();	//assuming the same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {

	//treat 0 and 1 letter strings as isograms
	if (Word.length() < 2) {
		return true;
	}

	TMap<char, bool> LetterSeen;	

	for (auto Letter : Word) {	//run through every letter
		Letter = tolower(Letter);	//turn the table case insensitive
		if (LetterSeen[Letter]) {	//if the letter is in the map
			return false;
		}
		else {
			LetterSeen[Letter] = true;	//add letter to the map as seen
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {

	for (auto Letter : Word) { //run through every letter
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}
