#include <iostream>
#include "menu.h"
//#include "mazeDisplayer.h"
//#include "mazeGenerator.h"

//NOTES:: Im going to use the stack to store data of unvisited neighboors, by using a stack its easy to keep
//  track of which nodes that have been visited/or not. as soon as some node doesnt have any more unvisited 
// neighboors it can be popped out of the stack, and this way the stack can be used for easy backtracking,
// all unvisited neighboors that we encounter gets pushed into the stack and set to "VISITED", and continue
// explore neighbors, The stack system can be used for recursion but also for a datastructure to keep track of
// the nodes that have been visited.
// 
// The recursive approach is going to be used to traverse the graph and make passing nodes as visited, and push
// them into the stack while traversing them, the stack can be use to keep track of unvisited neighbors that
// needs to be explored
// 
// NOTE: STACK USES LIFO
// 
// when a certain node has no unvisited neighbors left, that node gets popped from the stack, 
// and then the algorithm backtarcks to the previous node in the stack and continues the backtracking.
// 
//TODO::: Fixa Getters till alla medlemmer inom mazeNode och sen impplementera lösning för mazedisplayer.
// 
//  Goal::: lös problemet med mazedisplayer genom abstraktion.
//Tanken är att ha en abstrakt klass "interfaceMazeGenerator" som ska abstrahera bort själva logiken 
// i mazeGenerator, men som ska kunna användas för att skickas in som input till t.ex mazeDisplayer, mazeDisplayer
// ska då kunna använda sig av detta abstrakta interface, och detta abstrakta interface i sig ska kunna ge 
// tillgång till funktionen i mazeGenerator som returnerar vektorn. Genom att introducera abstraktion 
// så räcker det för mazeDisplayer att veta att mazeInterface kan användas för att komma åt vektorn.

// in order to do this, menu . h must have access to the private struct node inside mazeGenerator, and then
// use a getter to return the generated mazeVEctor from the mazeGenerator objerct and pass that vector as an
// argument.

int main() {
	
	//the class menu navigates the flow of the overallt program, have communications with other classes
	// lets the user navigate and use the program and gives the user a visual interface with options.
	// will also start and generate the mazeGenerator class
	menu startMenu;
	//mazeDisplayer(mazeGenerator& mazeVector);
	

	return 0;
}