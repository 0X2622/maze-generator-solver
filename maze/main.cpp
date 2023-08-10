#include <iostream>
#include "menu.h"

//the purpose of the main() function is to just start/boot up the program, and then initate a menu object which will
//load up the application start screen and menu choices. 
// The object 'menu' is what will navigate the entire flow of the program, by providing a an initial visual interface,
// and communication with other classes that lets the user to use the program effectively.




//TODO kvar att fixa::
//  1: Kolla om copy ctr + copy assign + move ctr + move assign måste tilläggas i mazeGenerator.h och såfall om jag annars
// måste åtminstone sätta att dessa konstrutorer är = "delete" Men då jag endast använder en default ctr för detta program,
// så kanske det inte behövs ? 

//2: kolla att ja inkluderar biblioteken rimligt utan dubleringar. Dessa två punkter kan fixas på 30 min.


int main() {
	
	bool running = true; //boolean value that indicates that the program is running
	
	//while(true) makes the program run until the user explicitly chooses to terminate it through the startMenu of object
	// menu. The purpose of this section is to shower the user how the program works and what conditions that needs to
	// be met in order to terminate the program.
	while (running) {
		menu startMenu;
		if (startMenu.getInputVal() == 1) {
			running = false;
		}
	}
	return 0;
}