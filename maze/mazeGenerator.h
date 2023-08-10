#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H
#include "MazeNode.h"
#include <iostream>
#include <vector>
#include <stack>

//this class holds the matrix/maze datastructure, and is responsible for generating the datastructure.
//this class holds methods for dynamically allocating mazenodes, storing a 2D container that will hold the
//entire maze datastructure and nodes, and also additional methods and members for accessing and manipulating datamembers.

//the maze is generated with a recursive approach together with dynamic allocation for the mazenodes, 
// by using dynamic allocation we can avoid the potential of stack overflow if the program is to allow larger maze
// dimensions in the future (especially since resursive methods that goes deep can cause overflow on the stack).

//Since dynamic allocation is used, the destructor makes sure to delete all dynamically allocated nodes everytime that
//the objet goes out of scope to avoid memory leaks. 

//This class uses node-pointers to link the nodes. By using pointers it is easy to access, manipulate, link nodes
// and iterate through all the mazeNodes.

//in order to build and generate the maze, this class needs to have access with the mazenode datasatructure, which is
// why mazenode.h is included in this file to allow mazenode access and communication.

//this class uses the heap to store the maze nodes, and the stack to store pointer to the nodes. By storing the maze nodes
//on the heap (which are larger in size) and the pointers in the stack (which are fairly small in size compared to the
// maze nodes) we reduce the risk of stack overflow.


class mazeGenerator {

public:

	mazeGenerator(); //default constructor -> generates a maze by default size 6x6 dim.

	/*
	mazeGenerator(const mazeGenerator& rhs); //copy construct. take a referense of the rhs and copies the data
	mazeGenerator(mazeGenerator&& rhs); //move construct. takes rhs as a r-lavue and moves the data.

	mazeGenerator& operator=(const mazeGenerator& rhs); //copy assign
	mazeGenerator& operator=(mazeGenerator&& rhs); //move assign.

	void ErrorHandling(); //error handling during maze generation to prevent crash.
	void resetMaze(); //method that is used to erase the previous maze and then generate a new one ??
	*/

	void NodesGenerator(int mazeWidth, int mazeHeight); //generates the matrix by allocating mazenodes and the 2D mazeVector
	void maze_StartEndPOS(); //generates a random start and end position of each generated maze
	std::vector<MazeNode*> findNeighboors(); //finds unvisited node neighboors & returns pointers to the found neighbours
	void DFS_Generator(); //Generates the actual maze using Recursive DFS. More elaborate description in the .cpp file


	//getter method to access the mazeNodes. Will be used by external classes to print the maze.
	// const before the return type tells read access only since we do not want to modify the vector/maze
	// const before the function body tells this function is not allowed to modify data within the body
	const std::vector<std::vector<MazeNode*>>& getMazeVector() const;
	~mazeGenerator(); //destructor

private:
	
	//dimensions of the maze which will be set by the default constructor.
	//in a more elaborate version of this application these values will be set by user input during runtime.
	int mazeWidth;
	int mazeHeigth;

	MazeNode* startNode; //pointer to access the maze startNode 
	MazeNode* endNode;//pointer to access the maze endNode
	MazeNode* currentPos; //keeps track of current position in the mazeGeneration (used in DFS)
	int x, y; // used for easier/more readable coordinate reference to a node
	int generateFlag = 0; //a flag that will indicate if a maze has been generated or not (used in DFS)

	//the stack will contain pointers to nodes. By using pointers to the node and not the nodes themselves,
	// reduce overhead of copying large amount of data. Since storing the memory addresses to the Node objects
	// takes less space than copying and saving the objects themselves, this can improve performance.
	std::stack<MazeNode*> mazeStack;

	//will contain pointers to all nodes in the entire maze. 
	//making it easy to iterate, manipulate, traverse and perform operations over all nodes in the maze.
	//std::vector<MazeNode*> nodesVector; // vector with node pointers to all nodes in the maze
	
	//the 2D matrix vector that will contain the whole matrix & maze datastructure.
	// The outer vector represent all matrix rows, while each inner vector represents a unique row
	// in the matrix, and the mazenode pointers represent the columns within each inner vector
	std::vector<std::vector<MazeNode*>> mazeVector; 
};

#endif // !MAZE_H


