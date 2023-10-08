#ifndef MAZEDISPLAYER_H
#define MAZEDISPLAYER_H
#include <vector>
#include <iostream>
#include<stack>

//forward declaration of the struct MazeNode, this allows us to declare MazeNode datatypes in the class
//without having to include the entire definition.
struct MazeNode;

// class that is used to create a visual represntation of the matrix, maze and the solved maze path
class mazeDisplayer {

private:
	int mazeWidth;
	int mazeHeight;

	//datatypes that represents the visual representation of matrix/maze
	// the purpose of the extended gaps is to make the maze a little bigger and more readable.
	const std::string Vert_wall = " | ";
	const std::string Hori_wall = "------"; 
	const std::string start = " S ";
	const std::string end = " E ";
	const std::string RegNode = " * ";
	const std::string H_path = "     "; 
	const std::string V_path = "   ";

	//representation of the actual sovled maze path 
	const std::string MazePathLeft = " < ";
	const std::string MazePathUp = " ^ ";
	const std::string MazePathRight = " > ";
	const std::string MazePathDown = " v ";

	std::string context; //will be used in printNodeRow to determine it's behaivour
	const std::vector<std::vector<MazeNode*>>& mazeVec; //reference to vector that holds the maze datastructure
	std::stack<MazeNode*> NodeStack;
	MazeNode* Tracker;
	MazeNode* StartNode = nullptr;//this node will be set as the start node to solve the maze path
	MazeNode* EndNode = nullptr;//end node that will be set as the goal for solving the maze

public:
	mazeDisplayer() = delete; //default ctr is not to be available since the mazeVector is needed as argument

	//constructor that takes in the generated 2D mazeVector as input
	mazeDisplayer(const std::vector<std::vector<MazeNode*>>& mazeVec);

	void printMatrix(); //creates just the 2D matrix structure with it's cells, nodes and walls.
	void printMaze(); //method that is used to print the complete generated maze.
	void printHorisontalWall(); //prints a horrisontal wall over a complete mazeRow
	void printMazeRow(const std::vector<MazeNode*>& mazeRow); //creates a complete maze/matrix row
	void analyzeRightPtr(MazeNode* MazeNode); //analyzes the right ptr of a node 
	void analyzeDownPtr(const std::vector<MazeNode*> mazeRow);//analyzes the down ptr of a node
	void DFS_MazeSolver(); // solves the maze by analyzing the node pointers and its links
	void BackTrack(); // function used to backtrack the visual mazesolver to a previous position/node
	void returnToMenu(); // used to exit the maze solving process to return to the main menu
	~mazeDisplayer();
};

#endif // !MAZEDISPLAYER_H

