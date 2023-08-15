#include <iostream>
#include "menu.h"

//the purpose of the main() function is to just start/boot up the program, and then initate a menu object which will
//load up the application start screen and menu choices. 
// The object 'menu' is what will navigate the entire flow of the program, by providing a an initial visual interface,
// and communication with other classes that lets the user to use the program effectively.

//ToDo::

//1: 
// Fixa min screen.h. Kolla exakt vilka funktioner som anv�nds i koden o s�tt de som funktioner d�r.
//Fixa output f�r b�da namespaces - UI & Screen/cursor manipulation med ASCI Codes
// Fixa tutorial f�r anv�nd ASCI codes nedan, va de exakt g�r.
//Eventuellt implementera/flyta �ven "go left()" funktionerna osv (fr�n displayer) till screen.h.
//testa �ndra D till D22 i stegen se om de ger samma output. s�fall kan de g�ra koden snyggare.

//2: Skriv in en output som meddelar anv�ndaren att helsk�rm beh�vs f�r stora labyrinten f�r att pekaren inte ska
//g� snett.
//EVentuellt se om man kan l�sa s� labyrinten inte blir CP om man k�r p� liten sk�rm men tror inte det.

//3:St�da bort alla stora kommentarer, och l�gg p� minimalistiska sj�lvf�rklarande kommentarer f�r hela koden.

//4: Skriv in namn, datum, osv p� varje fil, komprimera och l�mna in



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