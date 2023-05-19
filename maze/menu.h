#ifndef MENU_H
#define MENU_H 
#include <iostream>
#include <vector>
#include <cstdlib> // for exit() to terminate the program
#include <iomanip> // for setw() and left (kanske kan ta bort) -> tror inte ja använder detta.
//#include "mazeSolver.h"

struct MazeNode;

//interface of the main menu
////the class menu navigates the flow of the overallt program, have communications with other classes
// lets the user navigate and use the program and gives the user a visual interface with options.


class menu {
private:

	int inputOption; //will be used for all inputs for the different menus.
	int mazeWidth;
	int mazeHeight;

	//upper and lower bounds for input values
	int upperBound;
	int lowerBound;

	bool validInput = false; //used for errorcheck for multiple functions
	int int_errorFlagBit; // 0 == error, 1 == no error
	std::string errorMsg_RANGE; //errorMessages. WIll be different depending on function and error.
	std::string errorMsg_TYPE = "Error: Invalid input type. Make sure to input a value of type integer.";
	//mazeGenerator* mazeGenInstance;


public:
	menu(); //default constructor 
	void startMenu(); //visual interface of the startmenu and its options
	void mazeMenu();
	int inputMazeDim(std::string dimension);
	void inputMazeAlg();
	void input(); 
	bool inputErrorCheck();
	void flushBuffer(); //flushes the cin buffer
	~menu(); //destructor

};
#endif // !MENU_H

