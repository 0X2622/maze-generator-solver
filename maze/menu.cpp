#include "menu.h"
#include "mazeGenerator.h" //in order to create a mazeGenerator object
#include "mazeDisplayer.h" //in order to create a mazeDisplayer object
#include "ScreenManipulation.h"

//default ctr - generates the interface and menu for the program. calls the function startMenu
menu::menu()
{
	this->startMenu();
}

// Function that handles the flow of the entire program. It can interact with the mazeGenerator to retrieve
// the mazeVector (datastructure), and it can interact with the mazeDisplayer to pass the mazeVector.
// this function also interacts with all necessary functions to create the maze
void menu::startMenu()
{
	ScreenManipulation::mainMenuPrint(); //access screenoutput for mainmenu 

	// cursor will return to this marked point and not overwrite the visual menu content above when reloading
	ScreenManipulation::SaveCursorPos();
	this->Context = "StartMenu"; //sets the current contect of the program to determine its behavior
	this->errorMsg_Value = " 0, 1 or 2."; //Error msg: only acceptable input values for this function
	input(); //start the input options that lets the user make an input

	if (inputValue == 0) {
		ScreenManipulation::ClearScreen(); //So that the new matrix print will be position at a blank screen	
		const mazeGenerator mazeObj; //creates a mazeGenerator-object that can access the maze datastructure
		const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector();//access the mazeVector
		mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
	}
	else if (inputValue == 1) {
		ScreenManipulation::ClearScreen();
		MazeMenu(); //starts the menu which lets the user to determine maze dimensions and create the maze
		inputValue = 0; // reseting the input value to prevent termination of the program.
		const mazeGenerator mazeObj(mazeWidth, mazeHeight); //maze-object with userdefined dimensions
		const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector(); //access the mazevector
		mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
	}
	else if (inputValue == 2) { //inputValue == 2 will make main.cpp terminate the program
		std::cout << "Terminating program." << std::endl;
		return;
	}
}

//menu for letting the user to generate a maze of a different dimension,
void menu::MazeMenu()
{	
	//sets the lower and upper limit for maze dimensions.
	this->errorMsg_Value = "2 and 24";
	this->option1 = 2; //set the new values of option 1 && 2 for the MazeMenu. This is allowed range.
	this->option2 = 24;
	this->Context = "Dimension";
	this->mazeWidth = InputMazeDim("Choose desired maze width: ");
	this->mazeHeight = InputMazeDim("Choose desired maze height: ");
}

//This function is used to let the user to set a desired dimension. It will evaluate if the desired value is 
//alowed - and in that case it will return that value as a valid dimension.
int menu::InputMazeDim(std::string dimensionMsg)
{
	std::cout << dimensionMsg << std::endl;
	ScreenManipulation::SaveCursorPos(); // Save current cursor position under the menu text
	input(); //this will make sure that the returned value is allowed.
	return this->inputValue; //returns the input data to the dimension - which will be a given dimension.
}

//For every scenario that the user can make an input, this function is used to validate the input to make sure it's 
//allowed given the context. As long as the input is not valid, this function will iterate until it is valid, making it
//impossible for a user to enter invalid values for the options of the program.
void menu::input(){

	//initially sets inital condition to false so it can be set to true if the input is of a correct type/value
	this->validInput = false; 

	//while validInput == false, this function will keep iterate and ask user for a correct input type.
	while (this->validInput == false) {
		std::cin >> this->inputValue; //for each iteration, user gets to input an option.

		//means that the user is in the context of choosing a maze dimension
		if (Context == "Dimension") {
			if (inputValue < option1 || inputValue > option2) { //if the input by the user is lower or greater than the range limit
				this->int_errorFlagBit = 2; //marks that the user has made an invalid input range for this context
				this->validInput = inputErrorCheck(); //validInput == false in this scenario
			}
			else if (inputValue > option1 || inputValue < option2) { //if the inputValue is within the value range and the type is not wrong
				this->int_errorFlagBit = 1; //indicates that the input is correct and allowed
				this->validInput = inputErrorCheck(); //validInput = True in this scenario.
			}
		}
		//Means that the user is in the context of choosing an option in the start menu
		else if (Context == "StartMenu") {
			//if the input is not exactly one of the menu options:  
			if (inputValue != option1 && inputValue != option2 && inputValue!=option3) {
				this->int_errorFlagBit = 0; //indicates wrong input value for this context.
				this->validInput = inputErrorCheck(); 
			}
			//if input value is of allowed type.
			else if(inputValue == option1 || inputValue == option2 || inputValue == option3) {
				this->int_errorFlagBit = 1; 
				this->validInput = inputErrorCheck();
			}
		}
	}
}

//Will evaluate if there has been an incorrect/invalid input by the user. 
//This evaluation is done by checking the value of the error flag bit, which will indicate if there has been an
//invalid input and also what type of invalid input.
//in the case of an invalid input type (char instead of int), the cin buffer will be checked for a potential fail bit.
bool menu::inputErrorCheck()
{
	//cin.fail() checks for a fail bit in the cin buffer, which will tell if the user has made an invalid input type
	if (std::cin.fail()) { 
		ScreenManipulation::ClearLine();// Makes sure that the entire last error message output is cleared before print new.
		std::cout << this->errorMsg_TYPE << std::endl; //print error message 
		std::cin.clear(); // clears/resets the error flag bit in the buffer, so it can be used for future operations
		ScreenManipulation::flushBuffer(); //flushes remaining characters so it won't affect future inputs. 
		ScreenManipulation::RestoreAndClear(); // restores cursor position and clears the input line.
		return false; //returns false to the input function.
	}
	// flagbit evaluation: if flagbit == 0 means wrong input value for the start menu
	else if (this->int_errorFlagBit == 0) { //case for wrong input value
		std::cout <<"Error: Invalid input Value. Choose option between the values " <<errorMsg_Value;
		ScreenManipulation::RestoreAndClear();
		return false;
	}
	// flagbit == 2 means wrong input value for the maze dimension menu
	else if (this->int_errorFlagBit == 2){
		ScreenManipulation::ClearLine(); //clears previous printed error message.
		std::cout << "Error: Invalid input value. Choose a dimension between the values " << errorMsg_Value;
		ScreenManipulation::RestoreAndClear();
		return false;
	}
	//1 indicates no error
	else if(this->int_errorFlagBit == 1){
		ScreenManipulation::ClearLine(); //clears the line from previous error message.
		return true;
	}
}

//getter for the input value that is used in the main.cpp function.
//its used to indicate how the program functions from a high level and what conditions that terminates the program
double menu::getInputVal()
{
	return this->inputValue;
}

menu::~menu()
{
}


