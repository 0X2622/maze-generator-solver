#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>


/*
	USED ASCI CODE COMMANDS: 

	 /033   -> Escape character that signals the start of an escape sequence
	\033[s  -> Saves Cursor position at a particular point on the console that can be restored
	\033[2J -> Commands the terminal to clear the entire screen.


*/


//Purpose of this header is to contain namespaces that is for screen manipulation and screen outputs, trying to 
//sepparate logic and UI-outputs, UI-manipulations, etc. 

//namespace of Screen Manipulation functions such as clearing screen, moving the cursor, etc. 
namespace ScreenManipulation {
	void SaveCursorPos() { std::cout << "\033[s"; }
	void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }	// \033[2J Clears screen and 1;1H moves the cursor up to row 1. 
	void ClearLine(){ std::cout << "\033[2K"; } //clears the current line from previous output
	void RestoreAndClear() { std::cout << "\033[u" << "\033[K"; }//restores cursor pos & then clears line of previous output
}


//namespace of UI-outputs to the screen - such as menu choices, etc.
namespace ScreenOutputs {

}



#endif 

