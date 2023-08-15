#include "menu.h"
#include "mazeGenerator.h" //in order to create a mazeGenerator object
#include "mazeDisplayer.h" //in order to create a mazeDisplayer object
#include "Screen.h"

//default ctr - generates the interface and menu for the program. calls the function startMenu
menu::menu()
{
	this->startMenu();
}

//menu for letting the user to generate a maze of a different dimension,
void menu::MazeMenu()
{	
	//sets the lower and upper limit for maze dimensions.
	this->option1 = 2;
	this->option2 = 20;
	this->Context = "Dimension";
	this->mazeWidth = InputMazeDim("Choose desired maze width: ");
	this->mazeHeight = InputMazeDim("Choose desired maze height: ");

	//initiate 2 parameter constructor with the specified user mazewidth and height and create a reference to that object
	const mazeGenerator& mazeObj = mazeGenerator(mazeWidth, mazeHeight); 
	const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector(); //create a reference to the mazeVector
	mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
}

int menu::InputMazeDim(std::string dimension)
{
	std::cout << dimension << std::endl;
	ScreenManipulation::SaveCursorPos(); // Save current cursor position under the menu text
	input();
	return this->inputValue; //returns the input data to the dimension
}

void menu::startMenu()
{
	std::cout << "Welcome to mazegenerator. Choose one of the following options below: " << std::endl << std::endl;
	std::cout << "Press 0: To generate a maze by default size and DFS algorithm" << '\n' <<
				 "Press 1 to: Generate a maze of another dimension " << '\n'  <<
				 "Press 2 to: Terminate the program " << '\n' << '\n' << "Input option here: ";

	// the cursor will return to this marked point and not overwrite the visual menu content above when reloading the page.
	ScreenManipulation::SaveCursorPos();

	this->Context = "StartMenu"; //saves the current contect of the program
	this->errorMsg_Value = " 0, 1 or 2."; //sets the values that needs to be set by the user for this particular function
	
	//user input has to be exactly 1.0 or 0.0 in order to use the program.
	this->option2 = 1.0; 
	this->option1 = 0.0;
	
	input(); //start the input options that lets the user make an input

	if (inputValue == 0) {
		ScreenManipulation::ClearScreen(); //So that the new matrix print will be position at a blank screen at the top

		//creates a mazeGenerator object by initating it's default ctr. The default ctr will create a maze by default
		// size. 'mazeObj' will be a reference/alias to the generated object and thus refer to the same data,
		//this reference can then be used to retrieve the maze Datastructure from the object and pass it into mazeDisplayer
		const mazeGenerator& mazeObj = mazeGenerator(); //create referene to a default sized mazeObject
		const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector(); //create a reference to the mazeVector
		mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
	}
	else if (inputValue == 1) {
		ScreenManipulation::ClearScreen();
		MazeMenu(); //returns integer that tells which dimension that is to be used for the maze
	}
	else if (inputValue == 2) { 
		std::cout << "Terminating program." << std::endl;
		exit(0); // terminate program with exit code 0 - which means that the programs is terminating successfully
	}
}

//validates userinput by iterating until the user has entered a correct input that generates "validInnput" == "true"
void menu::input(){

	//initially sets inital condition to false so that it can be set to true *only* if the input is of a correct type/or value
	this->validInput = false; 

	//while validInput == false, this function will keep iterate and ask user for a correct input type.
	while (this->validInput == false) {
		std::cin >> this->inputValue; //for each iteration, user gets to input an option.

		//means that the user is in the context of choosing maze dimension
		if (Context == "Dimension") {
			if (inputValue < option1 || inputValue > option2) { //if the input by the user is lower or greater than the range limit
				this->int_errorFlagBit = 2; //marks that the user has made an invalid input range
				this->validInput = inputErrorCheck();
			}
			else if (inputValue > option1 || inputValue < option2) { //if the inputValue is within the value range and the type is not wrong
				this->int_errorFlagBit = 1; //indicates that the input is correct
				this->validInput = inputErrorCheck();
			}
		}
		//Means that the user is in the context of choosing an option in the start menu
		else if (Context == "StartMenu") {
			//invalid value check:: This conditions checks whether the user input has one of the values of 'lowerBound' and
			// 'upperBound', since all 3 of these values are set as "double", they need to be equal on the decimal in order
			// to return a value of "true" and allow the input as valid.
			if (inputValue != option1 && inputValue != option2 && inputValue!=option3) { //compares the input value to the available option values

				//value 0 indicates for wrong input value. This value will be used in inputErrorCheck for validation
				this->int_errorFlagBit = 0;
				this->validInput = inputErrorCheck(); //as long as the input value is invalid, this will return false
			}
			//if user input != invalid double value, -> errorFlag will be set == 1 to mark that,
			//if input == invalid value type (e.g. string/char), then this will also be handleled inside errorCheck
			else if(inputValue == option1 || inputValue == option2 || inputValue == option3) {
				this->int_errorFlagBit = 1; //indicates that the input was correct 
				this->validInput = inputErrorCheck();
			}
		}
	}
}

//errorCheck function. if the user input is valid/allowed and reaches the last else-statement it will return true, 
//if the function evaluates to true before that, means that the user input was invalid and this function will return false.
//based on found error, the function will display different messages to the user and handle the error differently.
bool menu::inputErrorCheck()
{
	//first conditions checks whether the user has not entered the right input type - for example entering a character when the type needs
	// to be an int, if true means that the cin-buffer will have a fail bit and cin.fail == true. 
	if (std::cin.fail()) { //if there is a fail bit in the cin buffer: 
		ScreenManipulation::ClearLine();// Clear the entire line to make sure that previous input is properly cleared
		std::cout << this->errorMsg_TYPE << std::endl; //print error message that prints "wrong input type".
		std::cin.clear(); //clears/resets the error flag bit in the buffer, so it can be used for future operations
		flushBuffer(); //"flushes out" remaining characters from the cin buffer
		ScreenManipulation::RestoreAndClear(); // restore cursor position to the current (user input) line
		return false; //returns false to the input function.
	}
	//if the cin buffer does not have a fail bit but the error flag is still == 0 means that the user made a wrong input value for the main menu
	else if (this->int_errorFlagBit == 0) { //case for wrong input value
		std::cout <<"Error: Invalid input Value. Choose option between the values " <<errorMsg_Value;
		flushBuffer(); //flushes the buffer from previous invalid input characters
		ScreenManipulation::RestoreAndClear();
		return false;
	}
	//if the cin buffer does not have a fail bit but the error flag is still == 0 means that the user made a wrong input value for the dimension menu
	else if (this->int_errorFlagBit == 2){ //the user made an invalid input for the maze Dimensions.
		ScreenManipulation::ClearLine();
		std::cout << "Error: Invalid input value. Choose a dimension between the values " << errorMsg_Value;
		flushBuffer(); //flushes the buffer from previous invalid input characters
		ScreenManipulation::RestoreAndClear();
		return false;
	}
	else{ // no range error or no type error. Errorbit = 1 indicates no range error.
		std::cout << "\033[K"; // no error -> clears line for next input
		return true;
	}
}


//this method flushes/discards the remaining characters inside the cin buffer.
//this is important so that invalid left over characters is not remaining in the cin buffer during the next user input.
//by clearing the buffer after each invalid input we create a new fresh buffer that the next user input is not affected
// by the previous one.
void menu::flushBuffer()
{
	//every time that cin.get() reads a character from the buffer, it then gets removed.
	// so cin.get() will read one character at a time from the buffer until it reaches a new line, effectively
	// flushing the buffer
	while (std::cin.get() != '\n') {
		continue;
	}
}

//används denna ? 
double menu::getInputVal()
{
	return this->inputValue;
}

menu::~menu()
{
}


