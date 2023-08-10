#include "menu.h"
#include "mazeGenerator.h" //in order to create a mazeGenerator object
#include "mazeDisplayer.h" //in order to create a mazeDisplayer object

//default ctr - generates the interface and menu for the program. calls the function startMenu
menu::menu()
{
	this->startMenu();
}

void menu::startMenu()
{
	std::cout << "Welcome to mazegenerator. Choose one of the following options below: " << std::endl << std::endl;
	std::cout << "Press 0: To generate a maze by default size and DFS algorithm" << '\n' <<
				 "Press 1 to: Terminate the program " << '\n' << '\n' << "Input option here: ";

	// Save current cursor position. By saving its position below the visual menu content (above), 
	// the cursor will return to this point and not overwrite the visual menu content when reloading the page.
	std::cout << "\033[s";

	//option 1 & 2 makes sure that the user input has to be exactly 1.0 or 0.0 in order to navigate the program.
	this->option2 = 1.0; 
	this->option1 = 0.0;
	this->errorMsg_Value = " 0.0 and 1.0"; //sets the values that needs to be set by the user for this particular function (kanske kan ta bort)
	input(); //start the input options that lets the user make an input

	if (inputValue == 0) { //if user effectively chose option 0
		std::cout << "\033[2J\033[1;1H"; //clears screen

		//creates a mazeGenerator object by initating it's default ctr. The default ctr will create a maze by default
		// size. 'mazeObj' will be a reference/alias to the generated object and thus refer to the same data,
		//this reference can then be used to retrieve the maze Datastructure from the object and pass it into mazeDisplayer
		const mazeGenerator& mazeObj = mazeGenerator(); //create referene to a default sized mazeObject
		const std::vector<std::vector<MazeNode*>>& mazeVec = mazeObj.getMazeVector(); //create a reference to the mazeVector
		mazeDisplayer displayer(mazeVec); //pass the mazeVector into the class mazeDisplayer to print the maze
	}
	else if (inputValue == 1) { //if user effectively chose option 1
		std::cout << "Terminating program." << std::endl;
		exit(0); // terminate program with exit code 0. 0 means that the programs is terminating successfully
	}
}

//validates userinput by iterating until the user has entered a correct input that generates "validInnput" == "true"
void menu::input(){
	//sets inital condition to false so that it can be set to true *only* if the input is of a correct type/or value
	//this->validInput = false; <--- Kan nog ta bort detta.

	//while validInput == false, this function will keep iterate and ask user for a correct input type.
	while (this->validInput == false) {
		std::cin >> this->inputValue; //for each iteration, user gets to input an option.

		
		//invalid value check:: This conditions checks whether the user input has one of the values of 'lowerBound' and
		// 'upperBound', since all 3 of these values are set as "double", they need to be equal on the decimal in order
		// to return a value of "true" and allow the input as valid.
		if (inputValue != option1 && inputValue != option2){ //compares the input value to the available option values
			
			//value 0 indicates for wrong input value. This value will be used in inputErrorCheck
			this->int_errorFlagBit = 0; 
			this->validInput = inputErrorCheck(); //as long as the input value is invalid, this will return false
		}

		//if user input != invalid double value, -> errorFlag will be set == 1 to mark that,
		//if input == invalid value type (e.g. string/char), then this will also be handleled inside errorCheck
		else {
			this->int_errorFlagBit = 1; //indicates that the input value was not wrong
			this->validInput = inputErrorCheck();
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
		std::cout << "\033[2K"; // Clear the entire line to make sure that previous input is properly cleared (was needed)
		std::cout << this->errorMsg_TYPE << std::endl; //print error message that prints "wrong input type".
		std::cin.clear(); //clears/resets the error flag bit in the buffer, so it can be used for future operations
		flushBuffer(); //"flushes out" remaining characters from the cin buffer
		std::cout << "\033[u"; // restore cursor position to the current (user input) line
		std::cout << "\033[K"; // clears from the cursor position to the end of the line from previous output so that the user can make a new try.
		return false; //returns false to the input function.
	}
	else if (this->int_errorFlagBit == 0) { //case for wrong input value
		//std::cout << "\033[2K"; // Clear the entire line
		std::cout <<"Error: Invalid input. Choose an integer that represents one of the options in the menu (0 or 1) "  << std::endl;
		flushBuffer(); //flushes the buffer from previous invalid input characters
		std::cout << "\033[u"; // restore cursor position to the current line
		std::cout << "\033[K"; // clear line from previous output
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

double menu::getInputVal()
{
	return this->inputValue;
}

menu::~menu()
{
}


