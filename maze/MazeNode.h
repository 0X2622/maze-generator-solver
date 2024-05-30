#ifndef MAZENODE_H
#define MAZENODE_H
#include <iostream>

//the entire structure of a single mazenode.
// The node is it's own defined type so that external objects can access it's private members through it's getter methods.

// Different nodeTypes, Enum type provides readability and also the ability for using switch-cases
enum NodeType { START, END, REGULAR}; 
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

	//constructor that creates a new node object. 
	//the pointers are initially set as null, and only the pointer that will create a path will be set as a link to other
	// nodes. All nodetypes are initally set as "REGULAR", since a defined START and END node has not yet been defined yet,
	MazeNode(std::pair<int, int> Coordinates) :Coordinates(Coordinates),
		up(nullptr), down(nullptr), left(nullptr), right(nullptr), nodeType(NodeType::REGULAR) {};

	//setters for the mazenode pointers. Used for linking nodes
	void setUpPtr(MazeNode* node) { this->up = node; };
	void setDownPtr(MazeNode* node) { this->down = node; };
	void setLeftPtr(MazeNode* node) { this->left = node; };
	void setRightPtr(MazeNode* node) { this->right = node; };

	//getters for node pointers (will be used for the print function to print path between linked nodes)
	MazeNode* getUpPtr() const { return this->up; };
	MazeNode* getDownPtr() const { return this->down; };
	MazeNode* getLeftPtr() const {return this->left; };
	MazeNode* getRightPtr() const { return this->right; };

	//used for setting information if a node has been backtracked to aid the cursor during the mazesolving
	//backtracking process -> it needs to know how to behave when paths has been backtracked already
	void SetBackTracked(bool tracked) { this->BackTracked = tracked; };
	bool GetBackTracked() const { return this->BackTracked; }; //kolla om denna används.

	const bool getVisited() const { return this->visited; }; //gets the visited status of a node, used by FindNeighboors
	void setVisited(bool marked) { this->visited = marked; }; //setter for the mazenode visited status. Used by DFS

	//setters for the node coordinates. Currently not used since the coordinates are set with the constructor.
	void setCoordinatesFirst(int x) { this->Coordinates.first = x; };
	void setCoordinatesSecond(int y) { this->Coordinates.second = y; };

	//getters for the node coordinates. Used by mazeGenerator to access node coordinates
	int getCoordinatesFirst() const { return this->Coordinates.first; };
	int getCoordinatesSecond() const { return this->Coordinates.second; };

	//setter for the nodeType value. Used by the function startendPos to set the nodeTypes
	void setNodeType(NodeType type) { this->nodeType = type; }; 
	NodeType getNodeType() const { return this->nodeType; }; //getter for node type - used for mazeDisplay print function
};
#endif // !MAZENODE_H

