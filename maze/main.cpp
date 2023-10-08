#include <iostream>
#include "menu.h"

//NEXT: St�da Resten av mazegenerator - DFS + findNeighboors

//the purpose of the main() function is to just start/boot up the program, and then initate a menu object which will
//load up the application start screen and menu choices. 
// The object 'menu' is what will navigate the entire flow of the program, by providing a an initial visual interface,
// and communication with other classes that lets the user to use the program effectively.

//ToDo::

//Coding conventions att fixa:
//1 : Se till att allt �r camelcase med f�rsta bokstaven som lowerCase.
//2: Se till att ha en abstrakt f�rklaring till varje funktion, och �verl�t detaljerna till mig/de som �r intresserade.
//3: se till att alla funktionsnamn och variabelnamn beskriver deras syfte p� ett intuitivt s�tt
//3:St�da bort alla stora kommentarer, och l�gg p� minimalistiska sj�lvf�rklarande kommentarer f�r hela koden.
//4: Skriv in namn, datum, osv p� varje fil, komprimera och l�mna in


// obs tekniskt sett kan ja skita i while-loopen o bara skapa objektet. Tror koden o programmet k�rs �nd� o det �r 
// mindre komplext ? 
int main() {

	bool running = true; //boolean value that indicates that the program is running
	
	//while(true) makes the program run until the user explicitly chooses to terminate it through the startMenu of object
	// menu. The purpose of this section is to shower the user how the program works and what conditions that needs to
	// be met in order to terminate the program.
	while (running) {
		menu startMenu;
		if (startMenu.getInputVal() == 2) {
			running = false;
		}
	}
	return 0;
}