#include <iostream>
#include "menu.h"

//NEXT: Städa Resten av mazegenerator - DFS + findNeighboors

//the purpose of the main() function is to just start/boot up the program, and then initate a menu object which will
//load up the application start screen and menu choices. 
// The object 'menu' is what will navigate the entire flow of the program, by providing a an initial visual interface,
// and communication with other classes that lets the user to use the program effectively.

//ToDo::

//Coding conventions att fixa:
//1 : Se till att allt är camelcase med första bokstaven som lowerCase.
//2: Se till att ha en abstrakt förklaring till varje funktion, och överlåt detaljerna till mig/de som är intresserade.
//3: se till att alla funktionsnamn och variabelnamn beskriver deras syfte på ett intuitivt sätt
//3:Städa bort alla stora kommentarer, och lägg på minimalistiska självförklarande kommentarer för hela koden.
//4: Skriv in namn, datum, osv på varje fil, komprimera och lämna in


// obs tekniskt sett kan ja skita i while-loopen o bara skapa objektet. Tror koden o programmet körs ändå o det är 
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