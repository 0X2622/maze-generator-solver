#ifndef MENU_H
#define MENU_H 
#include <iostream>
#include <vector>

//interface of the main menu
////the class menu navigates the flow of the overallt program, have communications with other classes
// lets the user navigate and use the program and gives the user a visual interface with options.
class menu {
private:

	// used for allowed ranges for maze dimension. Not mutable.
	const int MazeLowLimit = 2; 
	const int MazeHighLimit = 20;

	//values for the main menu options. Not mutable.
	const double MenuOptionOne = 0.0; 
	const double MenuOptionTwo = 1.0; 
	const double TerminateProgram = 2.0; 

	//maze dimensions
	int MazeWidth;
	int MazeHeight;

	double UserInput; //will be used for all inputs for the different menus.
	std::string Context; // sets the context of the program to determine its behaivor

	// boolean used for errorcheck validation. Initial condition == false so that it can be set to true
	// only if the user input is of a correct type or value
	bool ValidInput = false;
	
	//errorMessages used for wrong input value & type
	std::string AllowedRange; //error string that is used to show allowed input values for the user
	const std::string INVALID_TYPE = "Error: Invalid input type. Use an integer."; //error string
	const std::string INVALID_RANGE = "Error: Invalid range. Use an integer between the values "; //error string
	int ERROR_BIT; // data that will give information about the input. 0 == error, 1 == no error

public:
	menu(); //default constructor 
	void startMenu(); //that menu that contains visual interface & start flow of the program
	void MazeMenu(); //starts logik for setting maze dimensions
	int InputMazeDim(std::string dimension); // setting maze dimensions
	void input(); //method used for validating user input
	bool inputErrorCheck(); //errorCheck method based on user input
	double GetUserInput(); //getter to terminate the program if value 2 is entered
	~menu(); //destructor (kolla om jag verkligen ska lämna detta default eller inte)
};
#endif // !MENU_H

