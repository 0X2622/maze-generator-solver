#include "ScreenManipulation.h"


//creates a fresh buffer for future cin-input by flushing the remaining characters inside the cin buffer.
// prevents new cin operations being affected by old remaining characters inside the buffer. 
void ScreenManipulation::flushBuffer()
{
	//every time that cin.get() reads a character from the buffer, it then gets removed.
	// so cin.get() will read one character at a time from the buffer until it reaches a new line, effectively
	// flushing the buffer
	while (std::cin.get() != '\n') {
		continue;
	}
}

void ScreenManipulation::SaveCursorPos() { std::cout << "\033[s"; }
void ScreenManipulation::ClearScreen() { std::cout << "\033[2J\033[1;1H"; }	// Clears entire screen and 1;1H moves the cursor up to row 1 column 1. 
void ScreenManipulation::ClearLine() { std::cout << "\033[2K"; } //clears the entire current line from previous output
void ScreenManipulation::RestoreAndClear() { std::cout << "\033[u" << "\033[K"; }//restores cursor pos & then clears line of previous output

// this function is used as a "press any key to continue" function for the user. First it uses the flushBuffer() 
// to clear the cin-buffer from any previous character so that it won't get automatically consumed by cin.get() 
// and then it calls cin.get() which will pause the program until any user input has been made,
void ScreenManipulation::pressAnyKey() {
	flushBuffer();
	std::cin.get();
}

//print function for the main menu. The purpose of having this code here it to make the .cpp filer cleaner with only logic
void ScreenManipulation::mainMenuPrint() {
	std::cout << "Welcome to mazegenerator. Switch to full screen and choose one of the following options below: " << std::endl << std::endl
		<< "Press 0: To generate a maze by default size and DFS algorithm" << '\n' <<
		"Press 1 to: Generate a maze of another dimension " << '\n' <<
		"Press 2 to: Terminate the program " << '\n' << '\n' << "Input option here: ";
}

void ScreenManipulation::restorePosition()
{
	std::cout << "\033[u";
}

void ScreenManipulation::smallStepLeft()
{
	std::cout << "\033[3D";
}

// 2A moves the cursor upp one row in the maze. 3D moves the cursor left 3 columns which is needed to keep the 
// traveling direction up straight
void ScreenManipulation::StepUp()
{
	std::cout << "\033[2A" << "\033[3D"; //move cursor up one level
}

// 2B moves the cursor down one row in the maze. Again 3 columns left is needed to keep the walking line straight.
void ScreenManipulation::StepDown()
{
	std::cout << "\033[2B" << "\033[3D";
}

// moves the cursor left one step which equals to the traveling distance from one cell to another
// for some reason, 9 column steps had to be taken here, the reason is yet unknown but it was the number that made it work.
void ScreenManipulation::StepLeft()
{
	std::cout << "\033[9D";
}

void ScreenManipulation::StepRight()
{
	//std::cout << "   ";
	std::cout << "\033[3C";
}
