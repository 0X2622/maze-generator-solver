#ifndef MAZEDISPLAYER_H
#define MAZEDISPLAYER_H
#include <vector>
#include <iostream>


// With forward declaration we declare the clasee mazeSolver before it's complete definition is available.
// By using forward declaration in this case, we can use the object mazeSolver as a parameter into the constructor
// without having to include the entire 'mazeSolver.h' file in this class. By doing this we reduce the chance
// or errors due to dependencies, and also reduce build/compilation time and overhead.


//class mazeGenerator;

//forward declaration/reference of the struct MazeNode, this allows us to declare MazeNode datatypes in the class
//without having to include the entire definition.
struct MazeNode;


//class used to display the generated datastructure from mazeGenerator which is the 2D matrix and the generated Maze
// The display will be a visual representation of the generated datastructure
class mazeDisplayer {

private:

	//datatypes that represents the visual representation of matrix/maze
	// the purpose of the extended gaps is to make the maze a little bigger and more readable.
	const std::string Vert_wall = " | ";
	const std::string Hori_wall = "------"; 
	const std::string start = " S ";
	const std::string end = " E ";
	const std::string RegNode = " * ";
	const std::string H_path = "     "; 
	const std::string V_path = "   ";

	std::string funType; //will be used in printNodeRow to determine it's behaivour
	const std::vector<std::vector<MazeNode*>>& mazeVec; //represents the passed in 2Dvector that holds the maze datastructure

public:
	mazeDisplayer() = delete; //explicitly say that a default ctr is not to be used since the mazeVector is needed as input

	//constructor that takes in the generated 2D mazeVector as input
	mazeDisplayer(const std::vector<std::vector<MazeNode*>>& mazeVec);

	void printMatrix(); //method that allows the user to see just the 2D matrix structure, with it's nodes and walls.
	void printMaze(); //method that is used to print the complete generated maze.
	void printHorisontalWall(); //method for printing a line of horrisontal walls that is used for the matrix top roof.
	void printNodeRow(const std::vector<MazeNode*>& mazeRow); //prints a row of mazeNodes + walls/paths 
	void analyzeRightPtr(MazeNode* MazeNode); //analyzes the right ptr of a node to determine if a wall/path should be there
	void analyzeDownPtr(const std::vector<MazeNode*> mazeRow);//analyzes the down ptr of nodes to generate wall/or path. 
	~mazeDisplayer();
};

#endif // !MAZEDISPLAYER_H

