#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H
#include "MazeNode.h"
#include <iostream>
#include <vector>
#include <stack>

//class that represent the datastructure of a maze.
class mazeGenerator {

public:

	mazeGenerator(); //default constructor -> generates a maze by default size 6x6 dim.
	mazeGenerator(int MazeWidth, int MazeHeight); //2 parameter ctr - generates maze of user defined size
	void nodesGenerator(int mazeWidth, int mazeHeight); //allocate mazenodes in the mazevector
	void startEndPOS(); //generates a random start and end position of each generated maze
	std::vector<MazeNode*> findNeighboors(); //finds unvisited node neighboors
	void DFS_Generator(); //Generates the actual maze using Recursive DFS. 
	void linkNodes(MazeNode*& const mazeDirection, MazeNode*& const currentPos); //function to link nodes


	//getter method to access the mazeNodes. Will be used by external classes to print the maze.
	const std::vector<std::vector<MazeNode*>>& getMazeVector() const;
	~mazeGenerator(); //destructor

private:
	
	//dimensions of the maze which will be set by the default constructor.
	//in a more elaborate version of this application these values will be set by user input during runtime.
	const int mazeWidth;
	const int mazeHeigth;

	MazeNode* startNode; //pointer to access the maze startNode 
	MazeNode* endNode;//pointer to access the maze endNode
	MazeNode* currentPos; //keeps track of current position in the mazeGeneration (used in DFS)
	int x, y; // used for easier/more readable coordinate reference to a node

	//the stack will contain pointers to nodes. 
	std::stack<MazeNode*> mazeStack;
	
	//the 2D matrix vector that will contain the whole maze datastructure.
	// The outer vector represent all matrix rows, while each inner vector represents all columns
	std::vector<std::vector<MazeNode*>> MazeVector; 
};

#endif // !MAZE_H


