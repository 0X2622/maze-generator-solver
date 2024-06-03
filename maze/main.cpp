#include <iostream>
#include "menu.h"

//the purpose of the main() function is to just start/boot up the program, and then initate a menu object which will
//load up the application start screen and menu choices. 
// The object 'menu' is what will navigate the entire flow of the program, by providing a an initial visual interface,
// and communication with other classes that lets the user to use the program effectively.

int main() {

	bool running = true; //boolean value that indicates that the program is running

	// This loop will keep track of the inputValue of the generated object. If the user explicitly sets the
	// inputvalue == 2 inside the start menu, then running == false and the iteration + program will terminate,
	// while the input value is not == 2, the iteration will continue and create new objects.
	// This will keep the program running until the user explicitly wants to terminate it.
	while (running) {
		menu startMenu;
		if (startMenu.getInputVal() == 2) {
			running = false;
		}
	}
	return 0;
}