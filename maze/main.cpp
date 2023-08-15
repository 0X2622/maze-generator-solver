#include <iostream>
#include "menu.h"

//the purpose of the main() function is to just start/boot up the program, and then initate a menu object which will
//load up the application start screen and menu choices. 
// The object 'menu' is what will navigate the entire flow of the program, by providing a an initial visual interface,
// and communication with other classes that lets the user to use the program effectively.

//ToDo::

//1: 
// Fixa min screen.h. Kolla exakt vilka funktioner som används i koden o sätt de som funktioner där.
//Fixa output för båda namespaces - UI & Screen/cursor manipulation med ASCI Codes
// Fixa tutorial för använd ASCI codes nedan, va de exakt gör.
//Eventuellt implementera/flyta även "go left()" funktionerna osv (från displayer) till screen.h.
//testa ändra D till D22 i stegen se om de ger samma output. såfall kan de göra koden snyggare.

//2: Skriv in en output som meddelar användaren att helskärm behövs för stora labyrinten för att pekaren inte ska
//gå snett.
//EVentuellt se om man kan lösa så labyrinten inte blir CP om man kör på liten skärm men tror inte det.

//3:Städa bort alla stora kommentarer, och lägg på minimalistiska självförklarande kommentarer för hela koden.

//4: Skriv in namn, datum, osv på varje fil, komprimera och lämna in



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