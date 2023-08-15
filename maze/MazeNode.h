#ifndef MAZENODE_H
#define MAZENODE_H
#include <iostream>

//the entire structure of a single mazenode.
// The node is it's own defined type so that external objects can access it's private members through it's getter methods.
//the getter methods will be used to both generate the maze datastructure but also to display the maze in mazeDisplayer.
// By delcaring the members as private and providing getter methods to access those members we still get encapsulation
// of the sensitive data that is not to be shown to the external world.

//enum is a user defined data type. By making a enum called nodeType which itself has 3 types "START, END, REGULAR", 
// and assigning each individual node to one of these types, we can distinguish between the 
// the starter node, end node and regular path nodes. By allowing these nodetypes mazeDisplayer can present each node
// differently depending on its enum type.
enum class NodeType { START, END, REGULAR}; 
struct MazeNode {

private:
	NodeType nodeType; //will be used to give each one it's own ENUM type
	bool visited = false; // sets false as default since all nodes are not visited initially.
	bool BackTracked = false;//a bool that tells if a node has been backtracked used in mazesolving

	//nodepointers that is used to link nodes to create a maze path. pointers that are not linked to a node, will indicate
	//that a maze wall needs to be generated instead of a maze path.
	MazeNode* up;
	MazeNode* down;
	MazeNode* left;
	MazeNode* right;

	//node coordinates. coordinates.first = the first value. coordinates.second = second value.
	std::pair<int, int> Coordinates;

public:

	//constructor that creates a new node object. It takes in 1 argument which is it's individual coordinates within
	// the matrix that will be given by the method "nodeGenerator". This constructor uses initializer list to initialize
	// class memebers, which reduces the overhead by normal initialization and increase efficency and cleaner code.
	//the pointers are initially set as null, and only the pointer that will create a path will be set as a link to other
	// nodes. All nodetypes are initally set as "REGULAR", since a defined START and END node has not yet been defined yet,
	MazeNode(std::pair<int, int> Coordinates) :Coordinates(Coordinates),
		up(nullptr), down(nullptr), left(nullptr), right(nullptr), nodeType(NodeType::REGULAR) {};

	//setters for the mazenode pointers. Used for linking nodes
	void setUpPtr(MazeNode* node) { this->up = node; }
	void setDownPtr(MazeNode* node) { this->down = node; };
	void setLeftPtr(MazeNode* node) { this->left = node; };
	void setRightPtr(MazeNode* node) { this->right = node; };

	//getters for node pointers (will be used for the print function to print path between linked nodes)
	MazeNode* getUpPtr() { return this->up; };
	MazeNode* getDownPtr() { return this->down; };
	MazeNode* getLeftPtr() {return this->left; };
	MazeNode* getRightPtr() { return this->right; };

	//used for setting information if a node has been backtracked to aid the cursor during the mazesolving
	//backtracking process -> it needs to know how to behave when paths has been backtracked already
	void SetBackTracked(bool tracked) { this->BackTracked = tracked; } 
	bool GetBackTracked() { return this->BackTracked; }

	const bool getVisited() const { return this->visited; } //gets the visited status of a node, used by FindNeighboors
	void setVisited(bool marked) { this->visited = marked; }; //setter for the mazenode visited status. Used by DFS

	//setters for the node coordinates. Currently not used since the coordinates are set with the constructor.
	void setCoordinatesFirst(int x) { this->Coordinates.first = x; };
	void setCoordinatesSecond(int y) { this->Coordinates.second = y; };

	//getters for the node coordinates. Used by mazeGenerator to access node coordinates
	int getCoordinatesFirst() { return this->Coordinates.first; };
	int getCoordinatesSecond() { return this->Coordinates.second; };

	//setter for the nodeType value. Used by the function startendPos to set the nodeTypes
	void setNodeType(NodeType type) { this->nodeType = type; }; 
	NodeType getNodeType() const { return this->nodeType; }; //getter for node type - used for mazeDisplay print function
};
#endif // !MAZENODE_H

