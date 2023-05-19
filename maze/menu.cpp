#include "menu.h"
#include "mazeGenerator.h" //so that the menu impementation file has knowledge aabout mazeGenerator.h
#include "mazeDisplayer.h"
//#include <limits> //used for dimensionsErrorCheck - 

//default ctr - generates the interface and menu for the program. calls the function startMenu
menu::menu()
{
	this->startMenu();
}

//void menu::setMazeInstance(mazeGenerator* mazeObj) {
	//mazeGenInstance = mazeObj;
//}



//void menu::generateMaze()
//{
	//mazeGenerator* mazeObj = new mazeGenerator();
//}

void menu::startMenu()
{
	std::cout << "Welcome to mazegenerator. Choose one of the following options below: " << std::endl << std::endl;
	std::cout << "Press 0: To generate a maze by default size and algorithm" << '\n' <<
		"Press 1 to: Generate a maze with specific size" << '\n' <<
		"Press 2 to: Terminate the program " << '\n' <<'\n' << "Input option here: ";
	
	// Save current cursor position
	std::cout << "\033[s";

	this->upperBound = 2;
	this->lowerBound = 0;
	this->errorMsg_RANGE = " 0 and 2";
	input();

	//this->int_errorFlagBit = 0;
	//this->validInput = false; //reset value
	
	switch(inputOption) {
		//default maze. the brackets makes sure that there is a limited scope for case 0 which will get popped
		// once the code goes out of the scope. after case 0 is done the mazeObj is destroyed.
	case 0: {
		std::cout << "\033[2J\033[1;1H"; //clears screen
		
		using MazeVector = std::vector<std::vector<MazeNode*>>;
		//using MazeVector = mazeGenerator::MazeVector;
		//kanske ja kan köra en move construct här istället? 
		//const mazeGenerator& mazeObj = mazeGenerator(); //initiates the default ctr and passes the vallue to mazeObj
		//const MazeVector& mazeVec = mazeObj.getMazeVector();
		//mazeDisplayer displayer(mazeVec);

		
		//mazeDisplayer displayObj;
		//displayObj.getMazeVec(mazeObj.getMazeVector());
		break; }
		
		//maze by specific size
		case 1:
			// sends the escape sequence to the terminal, clears the screen and moves the cursor to the top left corner
			//source: https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
			std::cout << "\033[2J\033[1;1H";
			this->mazeMenu();
			break;

		//exit program
		case 2:
			std::cout << "Terminating program." << std::endl;
			exit(0); // terminate program with exit code 0. 0 means that the programs is terminating successfully
			break;

		//error/none of the cases above (FIX ERROR CHECK) 
		default:
			break;
	}
}


//controls the flow of the next menu that is used to set maze dimension and maze algorithm
void menu::mazeMenu()
{
	std::cout << "Mazegenerator Menu" << '\n' << '\n'; //i want to keep this all the time while at the page


	this->mazeWidth = inputMazeDim("Choose desired maze width: "); 
	this->mazeHeight = inputMazeDim("Choose desired maze height: ");

	
	std::cout <<'\n' << "Press 0: To generate a maze with DFS" << '\n' <<
						"Press 1 to: Generate a maze with BFS" << '\n' <<
						"Press 2 to: Go back to main menu" << '\n';

	this->inputMazeAlg();

}

//logic for inserting maze dimensions
int menu::inputMazeDim(std::string dimension)
{
	std::cout << dimension; //generates input text on the screen
	
	// Save current cursor position
	std::cout << "\033[s";

	this->upperBound = 50;
	this->lowerBound = 4;
	this->errorMsg_RANGE = " 4 and 50";
	input();

	return this->inputOption; //returns the input data to the dimension
}

void menu::inputMazeAlg()
{
	//saving cursor position refers to saving the current location of the cursor on the 
	//terminal window so that it can be restored later. When the cursor position is restored, it is moved back to 
	//the saved location. By doing this, we save this positon, the cursor can move to another position in 
	//the text, and do prints, and then we can restore it to this point and do new prints, and keep
	//everything thats above this point. 
	std::cout << '\n' << "Input here: " << "\033[s"; //save cursor position
	
	this->upperBound = 2; 
	this->lowerBound = 0;
	this->errorMsg_RANGE = " 0 and 2";
	input();

	switch (this->inputOption) {
		std::cout << "\033[2J\033[1;1H"; //clears screen for the maze generation.

		//creates a mazeGenerator object with specified dimensions and integer that indicates the chosen algorithm.
		case 0: {
			mazeGenerator mazeObj(this->mazeWidth, this->mazeHeight, this->inputOption);
			break;
		}
		case 1: {
			mazeGenerator mazeObj(this->mazeWidth, this->mazeHeight, this->inputOption);
			break;
		}
		case 2: {
			std::cout << "\033[2J\033[1;1H"; //clears screen (läs på hur det funkar)
			//std::cout << "\033[u"; // restore cursor position to the current line
			//std::cout << "\033[K";
			this->startMenu();
			break;
		}
		default: {
			break;
		}
	}
}

void menu::input()
{
	this->validInput = false; //sets the condition to false before the loop
	while (this->validInput == false) {
		std::cin >> this->inputOption;
		//invalid integer value
		if (this->inputOption < this->lowerBound || this->inputOption > this->upperBound) {
			this->int_errorFlagBit = 0; // 0 indicates wrong input range
			this->validInput = inputErrorCheck();
		}
		//invalid input type
		else {
			this->int_errorFlagBit = 1; //indicates that the input range was not wrong
			this->validInput = inputErrorCheck();
		}
	}
}

//must check that the input is an integer.
//must check that the dimensions is reasonable (not too high and not too low)
bool menu::inputErrorCheck()
{
	//the design is multiple filters that checks if all conditions are met.
	//if the user has not specified mazeWidth or mazeHeight as an integer, a fail bit will be set in the
	// cin buffer, if this is the case then following error handling will occur: 
	if (std::cin.fail()) { //case for wrong input type
		std::cout << this->errorMsg_TYPE << std::endl;
		std::cin.clear(); //clears the cin flag/fail bit in the buffer so it can be used for future operaetions.
		flushBuffer(); //resets cin buffer from invalid characters	
		std::cout << "\033[u"; // restore cursor position to the current line
		std::cout << "\033[K"; // clear line from previous output
		return false;
	}
	else if (this->int_errorFlagBit == 0) { //case for wrong input value
		std::cout <<"Error: Invalid value. Input an integer between the values of " << this->errorMsg_RANGE << std::endl;
		std::cout << "\033[u"; // restore cursor position to the current line
		std::cout << "\033[K"; // clear line from previous output
		return false;
	}
	else{ // no range error or no type error. Errorbit = 1 indicates no range error.
		std::cout << "\033[K"; // no error -> clears line for next input
		return true;
	}
}

//flushes and resets the cin buffer when the user has made an illegal input
void menu::flushBuffer()
{
	// read characters from the input buffer until it reaches the newline character, 
	// effectively flushing the buffer.
	//cin.get() reads characters from the input buffer and returns an ascii value. iteration will continue
	// until the iterator reaches the endline.
	while (std::cin.get() != '\n') {
		continue;
	}
}


menu::~menu()
{
}


