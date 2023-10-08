#ifndef SCREENMANIPULATION_H
#define SCREENMANIPULATION_H
#include <iostream> //kanske kan ta bort

/*
	Purpose of this header is to contain namespaces that is for screen manipulation and screen outputs - trying to 
	sepparate logic and UI-outputs, UI-manipulations, etc. The purpose of implementing this is to make the logical code
	cleaner and more readable.

	ESCAPE SEQUENCES:
	Sources: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

	Used combinations: 
	 /033   -> Escape character that signals the start of an escape sequence
	\033[s  -> Saves Cursor position at a particular position "s" on the console that can be restored
	\033[1;1H" moves the cursor up to row 1 column 1, which is what the numbers stand for.
	\033[u -> Moves the cursor to a previously marked position on the screen (marked with \033[s) 
	\033[K -> Clears the rest of the current line from the cursor position and to the right
	\033[2K -> Clears the entire current line both right and left of the cursor position
	\033[2J -> Commands the terminal to clear the entire screen from top to botom.
	\033[1J -> clears the screen from the cursor to the top of the screen.
*/
namespace ScreenManipulation {

	void flushBuffer();
	void SaveCursorPos();
	//void restoreCursorPos() {} //får se om jag kommer behöva denna
	void ClearScreen();
	void ClearLine();
	void RestoreAndClear();
	void pressAnyKey();
	void mainMenuPrint();
	void restorePosition();
	void smallStepLeft();

	//check the source file above for instructions of how these functions work
	void StepUp();
	void StepDown();
	void StepLeft();
	void StepRight();
}

#endif 

