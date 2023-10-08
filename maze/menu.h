#ifndef MENU_H
#define MENU_H 
#include <iostream>
#include <vector>

//interface of the main menu
////the class menu navigates the flow of the overallt program, have communications with other classes
// lets the user navigate and use the program and gives the user a visual interface with options.
class menu {
private:

	//maze dimensions
	int mazeWidth;
	int mazeHeight;

	double inputValue; //will be used for all inputs for the different menus.
	double option1 = 0.0; //control value for the first menu option
	double option2 = 1.0; //control value for the second menu option.
	double option3 = 2.0; //option for terminating the program
	std::string Context; // sets the context of the program to determine its behaivor

	// boolean used for errorcheck validation. Initial condition == false so that it can be set to true
	// only if the user input is of a correct type or value
	bool validInput = false;
	int int_errorFlagBit; // data that will give information about the input. 0 == error, 1 == no error
	
	//errorMessages used for wrong input value & type
	std::string errorMsg_Value; //when the user makes an invalid value for an option.
	std::string errorMsg_TYPE = "Error: Invalid input type. Make sure to input an integer type."; 

public:
	menu(); //default constructor 
	void startMenu(); //that menu that contains visual interface & start flow of the program
	void MazeMenu();
	int InputMazeDim(std::string dimension);
	void input(); //method used for validating user input
	bool inputErrorCheck(); //errorCheck method based on user input
	double getInputVal();
	~menu(); //destructor (kolla om jag verkligen ska lämna detta default eller inte)
};
#endif // !MENU_H

