#include "menu.h"
#include "mazeGenerator.h" //in order to create a mazeGenerator object
#include "mazeDisplayer.h" //in order to create a mazeDisplayer object
#include "ScreenManipulation.h" //in ordet to navigate the cursor position for the user experience and GUI

//default ctr - generates the interface and menu for the program. calls the function startMenu
menu::menu(){
	this->startMenu();
}

// Function that handles the flow of the entire program. It can interact with the mazeGenerator to retrieve
// the mazeVector (datastructure), and it can interact with the mazeDisplayer to pass the mazeVector.
// this function interacts with all necessary functions to create and display the maze
void menu::startMenu(){
	ScreenManipulation::mainMenuPrint(); //access screenoutput for mainmenu 
	ScreenManipulation::SaveCursorPos(); //save cursor position to not overwrite the menu text when reloading
	this->Context = "StartMenu"; //sets the current contect of the program to determine its behavior
	this->AllowedRange = " 0, 1 or 2."; //error msg that shows allowed values for this particular menu
	input(); //calls the input method that lets the user make an input to the start menu

	if (UserInput == 0) { // -> Default 6 x 6 size
		ScreenManipulation::ClearScreen(); //clears screen and resets cursor position for maze generation preparation
		const mazeGenerator mazeObj; //creates a mazeGenerator object that can access the maze datastructure
		const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector();//access the mazeVector
		mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
	}
	else if (UserInput == 1) { // -> customized size 
		ScreenManipulation::ClearScreen();
		MazeMenu(); //starts the menu which lets the user to determine maze dimensions and create the maze
		UserInput = 0; // reseting the input value to prevent accidental termination of the program.
		const mazeGenerator mazeObj(MazeWidth, MazeHeight); //maze-object with userdefined dimensions
		const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector(); //access the mazevector
		mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
	}
	else if (UserInput == 2) { //inputValue == 2 will make main.cpp terminate the program
		std::cout << "Terminating program." << std::endl;
		return;
	}
}

//menu for letting the user to generate a maze of a different dimension,
void menu::MazeMenu(){	
	this->AllowedRange = "2 and 20"; //20 is the dimension limit that doesn't cause graphical bug
	this->Context = "Dimension"; //sets the program context to "dimension" to change program behaivor
	this->MazeWidth = InputMazeDim("Choose desired maze width: "); //calls the method 2 times, once for each dimension
	this->MazeHeight = InputMazeDim("Choose desired maze height: ");
}

//This function is used to let the user to set a desired dimension. It will evaluate if the desired value is 
//alowed - and in that case it will return that value as a valid dimension.
int menu::InputMazeDim(std::string dimensionMsg){
	std::cout << dimensionMsg << std::endl;
	ScreenManipulation::SaveCursorPos(); // Save current cursor position under the menu text
	input(); //this will make sure that the returned value is allowed.
	return this->UserInput; //returns the chosen user dimension up one level
}


// control function that makes sure that every user input is valid and allowed for the current context
// this function will iterate until the user input is valid, making invalid inputs impossible 
void menu::input(){

	//ensures that this value is always set to false to only be true if the input is of a correct type/value
	this->ValidInput = false; 

	//while validInput == false, this function will keep iterate and ask user for a correct input type.
	while (this->ValidInput == false) {
		std::cin >> this->UserInput; //for each iteration, user gets to input an option.

		//means that the user is in the context of choosing a maze dimension
		if (Context == "Dimension") {
			if (UserInput < MazeLowLimit || UserInput > MazeHighLimit) { //if user input is outside of the allowed range
				this->ERROR_BIT = 2; //marks that the user has made an invalid input range for this context
				this->ValidInput = inputErrorCheck(); //validInput == false in this scenario
			}
			else if (UserInput > MazeLowLimit || UserInput < MazeHighLimit) { //if the inputValue is within the value range and the type is not wrong
				this->ERROR_BIT = 1; //indicates that the input is correct and allowed
				this->ValidInput = inputErrorCheck(); //validInput = True in this scenario.
			}
		}
		//Means that the user is in the context of choosing an option in the start menu
		else if (Context == "StartMenu") {
			//if the input is not exactly one of the menu options:  
			if (UserInput != MenuOptionOne && UserInput != MenuOptionTwo && UserInput !=TerminateProgram) {
				this->ERROR_BIT = 0; //indicates wrong input value for this context.
				this->ValidInput = inputErrorCheck(); 
			}
			//if input value is of allowed type.
			else if(UserInput == MenuOptionOne || UserInput == MenuOptionTwo || UserInput == TerminateProgram) {
				this->ERROR_BIT = 1;
				this->ValidInput = inputErrorCheck();
			}
		}
	}
}

// Checks for invalid user inputs (type or range) by checking the value of the errorBit.
// in the case of an invalid input type (char instead of int) the cin buffer will be checked for a potential fail bit.
// in the case for invalid input range the previous input is cleared from the screen. 
// Invalid input will always return false, valid input will always return true.
bool menu::inputErrorCheck(){

	//cin.fail() checks for a fail bit in the cin buffer, which will tell if the user has made an invalid input type
	if (std::cin.fail()) { 
		ScreenManipulation::ClearLine();// clears any previous error message before new print
		std::cout << this->INVALID_TYPE << std::endl; //print error message 
		std::cin.clear(); // clears/resets the error flag bit in the buffer, so it can be used for future operations
		ScreenManipulation::flushBuffer(); //flushes remaining characters of the cin buffer so it won't affect future inputs. 
		ScreenManipulation::RestoreAndClear(); // restores cursor position and clears the input line.
		return false; //returns false to the input function.
	}
	// flagbit evaluation: if flagbit == 0 means wrong input value for the start menu
	else if (this->ERROR_BIT == 0) { //case for wrong input value
		std::cout << INVALID_RANGE << AllowedRange; //error message
		ScreenManipulation::RestoreAndClear();
		return false;
	}
	// flagbit == 2 means wrong input value for the maze dimension menu
	else if (this->ERROR_BIT == 2){
		ScreenManipulation::ClearLine(); //clears previous printed error message.
		std::cout << "Error: Invalid input value. Choose a dimension between the values " << AllowedRange;
		ScreenManipulation::RestoreAndClear();
		return false;
	}
	//1 indicates no error
	else if(this->ERROR_BIT == 1){
		ScreenManipulation::ClearLine(); //clears the line from previous error message.
		return true;
	}
}

//getter for the input value that is used in the main.cpp function.
//its used to indicate how the program functions from a high level and what conditions that terminates the program
double menu::GetUserInput(){
	return this->UserInput;
}

menu::~menu(){}


