#ifndef MAZEDISPLAYER_H
#define MAZEDISPLAYER_H
#include <vector>
#include <iostream>
#include<stack>
#include <thread> // for sleep
//#include <chrono>


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

	struct VisualNode {
	private:
		bool visited = false; //always set as false by default
		std::string NodeType; //can be " S ", " E " or " * ".
		VisualNode* up;
		VisualNode* down;
		VisualNode* left;
		VisualNode* right;

		std::pair<int, int> Coordinates;

	public:
		VisualNode(std::pair<int, int> Coordinates, std::string NodeType) :Coordinates(Coordinates),
			up(nullptr), down(nullptr), left(nullptr), right(nullptr), NodeType(NodeType) {};

		std::string GetNodeType() { return this->NodeType; };
		void SetNodeType(std::string type) { this->NodeType = type; }
		
		//setters for the visual nodepointers. Used for linking nodes
		void setUpPtr(VisualNode* node) { this->up = node; }
		void setDownPtr(VisualNode* node) { this->down = node; };
		void setLeftPtr(VisualNode* node) { this->left = node; };
		void setRightPtr(VisualNode* node) { this->right = node; };

		//getters for the visual node ptrs
		VisualNode* getUpPtr() { return this->up; };
		VisualNode* getDownPtr() { return this->down; };
		VisualNode* getLeftPtr() { return this->left; };
		VisualNode* getRightPtr() { return this->right; };

		const bool getVisited() const { return this->visited; } //gets the visited status of a node, used by FindNeighboors
		void setVisited(bool marked) { this->visited = marked; }; //setter for the mazenode visited status. Used by DFS

		//setters for the node coordinates. Currently not used since the coordinates are set with the constructor.
		void setCoordinatesFirst(int x) { this->Coordinates.first = x; };
		void setCoordinatesSecond(int y) { this->Coordinates.second = y; };

		//getters for the node coordinates. Used by mazeGenerator to access node coordinates
		int getCoordinatesFirst() { return this->Coordinates.first; };
		int getCoordinatesSecond() { return this->Coordinates.second; };

		//setter for the nodeType value. Used by the function startendPos to set the nodeTypes
		void setNodeType(std::string type) { this->NodeType = type; };
		std::string getNodeType() const { return this->NodeType; }; //getter for node type - used for mazeDisplay print function

	};

	int mazeWidth;
	int mazeHeight;
	int matrixGenerated_FLAG = 0;

	//datatypes that represents the visual representation of matrix/maze
	// the purpose of the extended gaps is to make the maze a little bigger and more readable.
	const std::string Vert_wall = " | ";
	const std::string Hori_wall = "------"; 
	//const std::string start = " S ";
	//const std::string end = " E ";
	//const std::string RegNode = " * ";
	const std::string H_path = "     "; 
	const std::string V_path = "   ";

	//representation of the actual sovled maze path 
	const std::string MazePathLeft = " < ";
	const std::string MazePathUp = " ^ ";
	const std::string MazePathRight = " > ";
	const std::string MazePathDown = " v ";

	std::string context; //will be used in printNodeRow to determine it's behaivour
	const std::vector<std::vector<MazeNode*>>& mazeVec; //represents the passed in 2Dvector that holds the maze datastructure
	std::vector<std::vector<VisualNode*>> VisualMazeVec;

	//data used for mazesolver
	int GenerateFlag = 0;
	std::stack<VisualNode*> NodeStack;
	VisualNode* Tracker;
	//MazeNode* StartNode = nullptr; //this node will be set as the start node to solve the maze path
	//MazeNode* EndNode = nullptr; //end node that will be set as the goal for solving the maze

	VisualNode* StartNode = nullptr;
	VisualNode* EndNode = nullptr;
	bool startBool = false;
	bool endBool = false;
	std::string LastDirection;


	//maybe i need to create a struct here that represents the characteristics of a visual string node
	//that will exist within the visualmazevector. Every visual string node will need 4 pointers
	// up, down left right, and while printing the visual maze I can link the nodes where a patah is to be.
	// this way - by having the visual string nodes linked to each other (to show where there is to be a path)
	// then the mazesolver algorithm/function can use these nodes to analyse every string node that it traverses
	// to see if that string node has a linking to another string node or not ? 

	

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
	//void findStartNode(); not needed anymore
	void NodesLinker();
	void FindNodeType();
	void DFS_MazeSolver();
	void setDimensions();
	void StepUp();
	void StepDown();
	void StepLeft();
	void StepRight();
	void BackTrack();
	~mazeDisplayer();
};

#endif // !MAZEDISPLAYER_H

