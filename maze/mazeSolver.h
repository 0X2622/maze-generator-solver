#ifndef MAZESOLVER_H
#define MAZESOLVER_H
#include "mazeGenerator.h" //the class mazeGenerator must be included to access the maze Datastructure

//class for solving the maze that has been generated
//This class shal not modify any resources or data structures from the mazeGenerator object.
// It shall have full access to the object and its recources in order to find a path to solve the maze with chosen
// algorithms. All recource allocation and handling is done by "MazeGenerator"
class mazeSolver {
	
	//inputs::
	//the generated maze and it's data structure from class 'mazeGenerator'
	// algorithm and data structure to generate a path
	// datastructure in how to represent a found path 

	//output
	// a generated path based on the recieved data above

public:

	//constructor that takes an m_generator reference object as input and stores it as a private member.
	// this member can then be used to access the maze data structure and solve the maze with the solve methods.
	mazeSolver(mazeGenerator& m_generator); 


	// maze solving algorithms. These methods will/shal contain data structure to represent a found path.
	// the found path can be represented as the given node coordinates/linked list of nodes, that simulates
	// the found path.
	void DFS_Solver();
	void BFS_Solver();

private:

	//method variable that holds reference to the mazeGenerator object.
	//this allows the salveSolver class to have access to the maze datastructure of the mazeGenerator,
	// and use it to solve the maze (with the solve methods). 
	// Important note: The mazeSolver class has only access to the maze datastructure for reading and solving,
	// and not for modifying the rescources and maze datastructure (since that is the responsibility of mazeGen)
	mazeGenerator& m_generator;
};

#endif // !MAZESOLVER_H

