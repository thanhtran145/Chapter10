#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//input (1) header files inputs validation
char inputChar(string prompt, string lookup);
int inputInteger(string prompt);
string inputString(string prompt, bool spaces);

//precondition:
//postcondition:
class AnimalGuessingGame {
private:
	string question;
	//this well be for yes
	AnimalGuessingGame* left;
	//this will be for no
	AnimalGuessingGame* right;
	//will hold the nodes 
	AnimalGuessingGame* root;
public:
	//default constructor
	AnimalGuessingGame();
	AnimalGuessingGame(const string& data);
	//deconstructor
	~AnimalGuessingGame();
	//delete tree
	void deleteEntireTree(AnimalGuessingGame* node);

	void theTree();
	void saveToFile(AnimalGuessingGame* node, ostream& file);

	void playGame(AnimalGuessingGame* node);

	//member function for menu
	void mainInformation();
};
