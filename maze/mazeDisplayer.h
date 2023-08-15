#ifndef MAZEDISPLAYER_H
#define MAZEDISPLAYER_H
#include <vector>
#include <iostream>
#include<stack>
#include <thread> // for sleep


//forward declaration/reference of the struct MazeNode, this allows us to declare MazeNode datatypes in the class
//without having to include the entire definition.
struct MazeNode;


//class used to display the generated datastructure from mazeGenerator which is the 2D matrix and the generated Maze
// The display will be a visual representation of the generated datastructure
class mazeDisplayer {

private:
	int mazeWidth;
	int mazeHeight;
	int matrixGenerated_FLAG = 0;

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
	
	const std::vector<std::vector<MazeNode*>>& mazeVec; //represents the passed in 2Dvector that holds the maze datastructure

	//data used for mazesolver
	int GenerateFlag = 0;
	std::stack<MazeNode*> NodeStack;
	MazeNode* Tracker;

	MazeNode* StartNode = nullptr;//this node will be set as the start node to solve the maze path
	MazeNode* EndNode = nullptr;//end node that will be set as the goal for solving the maze

	//kolla om dessa används
	bool startBool = false;
	bool endBool = false;

	std::string StepDirection;
	std::string BackTrackDirection;

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
	void FindNodeType();
	void AdjustVisited();
	void AdjustStartPos();
	void DFS_MazeSolver();
	void StepUp();
	void StepDown();
	void StepLeft();
	void StepRight();
	void BackTrack();
	~mazeDisplayer();
};

#endif // !MAZEDISPLAYER_H

