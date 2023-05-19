#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H
#include "mazeInterface.h"
#include <iostream>
#include <vector>
#include <stack>

//rule of five:
//Since this class uses dynamic memory allocation, a destructor is needed to free up the allocated memory
// The rule of five sugguest, that if one of these components (constructor, copy constructor, destructor, etc.)
// is used, then all 5 will most likely be needed to handle rescources efficently and to avoid memory leaks,
// undefined behaviors, etc.

//raii::
// is a technikue, that lets the lifetime of allocated recources to be tied to the lifetime of the objects
// and thus we avoid memory leaks, etc. by implementing raii. raii is going to be used in this class to achieve
// the rule of five.


//inputs:: 
	//nodes -> maze size & dimensions (width & heigh), 
	//rescource allocation/de allocation -> raii approach. 
	//starting point & end point
	// seed value? to control the randomness of the generation.
	// DFS algorithm (recursive
	// 
	// Dynamic allocation:
	//since the user will have the option to input size of the maze during run time, dynamic allocation
	//is better suited, as it will allow the program to allocate memory during run time and flexibility
	// for this particular program, (while static allocation must be known in advance and fixed at compile time).
	// While using the stack for static allocation is a good approach, dynamic allocation provides flexibility
	//and scalabillity.
	// Additionally: Since I will use a recursive approach, dynamic memory allocation can be more efficent,
	// since the size of stack can increase fast and easy with larger mazes. 
	// Using dynamic allocation allows the program to allocate memory on demand while constructing the maze,
	// which is more efficent memory usage and also prevents from stack overflow.

	//outputs::
	// The generated maze (that consists of grid, cells, graphs/chosen data structure) that can be accessed
	// by the maze solver.
	//errors & exceptions that may occur during generation.

// FD must be done outside of class because if its done within the class, the compiler expects to see 
// the complete type of the struct when its defined within the class.
//struct MazeNode; //forward declaration of struct MazeNode. 

//Holding the Maze datastructure -> class for generating maze (nodes, DFS, cells, walls, etc.)
class mazeGenerator  : public mazeInterface  {

public:



	//the entire structure of a single node. 
	struct MazeNode {
	private:
		bool visited = false; //true or false -> sets false as default.
		bool flag = false; //a flag that will be set on each visited cell to flaga it as visited (behövs??)

		// pointers that is pointing to a neighbouring node, each direction.
		// these pointers will be used to link the nodes and also to generate walls between the nodes
		MazeNode* up;
		MazeNode* down;
		MazeNode* left;
		MazeNode* right;

		std::pair<int, int> Coordinates; //coordinates.first = x. coordinates.second = y

		int index = 0; // behövs ? kolla om ja accessar indexet inom mazenode vid något tillfälle

	public:
		//creates new node object with coordinates. The pointers is initially set to nullptr as default (why?).
		// after all nodes has been generated the pointers will be set to it's neighboors to link the nodes.
		MazeNode(std::pair<int, int> Coordinates) :Coordinates(Coordinates),
			up(nullptr), down(nullptr), left(nullptr), right(nullptr) {};

		//setters for the mazenode pointers
		void setUpPtr(MazeNode* node) { this->up = node; }
		void setDownPtr(MazeNode* node) { this->down = node; };
		void setLeftPtr(MazeNode* node) { this->left = node; };
		void setRightPtr(MazeNode* node) { this->right = node; };
		
		bool getVisited() { return this ->visited; } //getter for the mazeNode visited value
		void setVisited(bool marked) { this->visited = marked; }; //setter for the mazenode visited flag

		//setters for the node coordinates.
		void setCoordinatesFirst(int x) { this->Coordinates.first = x; };
		void setCoordinatesSecond(int y) { this->Coordinates.second = y; };
		
		//getters for the node coordinates.
		int getCoordinatesFirst() { return this->Coordinates.first; };
		int getCoordinatesSecond() { return this->Coordinates.second; };
		
		//int getFlag() { return this->flag; }; kanske inte behövs
		//void setFlag() { return this->flag; };

		MazeNode* getMazePtr() const {};
	};



	//typedef of the type maze vector, makes the type more readable in the program.


	//constructors below:
	mazeGenerator(); //default constructor -> generates a maze by default size 6x6 dim. (behövs explicit?)

	//3 parametrisized ctr -> used for user input to create desired size
	mazeGenerator(int MazeWidth, int Mazeheigh, int algorithm);

	/*
	mazeGenerator(const mazeGenerator& rhs); //copy construct. take a referense of the rhs and copies the data
	mazeGenerator(mazeGenerator&& rhs); //move construct. takes rhs as a r-lavue and moves the data.

	mazeGenerator& operator=(const mazeGenerator& rhs); //copy assign
	mazeGenerator& operator=(mazeGenerator&& rhs); //move assign.

	void ErrorHandling(); //error handling during maze generation to prevent crash.
	void resetMaze(); //method that is used to erase the previous maze and then generate a new one ??
	*/


	//generates a 2D matrix of Nodes, with a size that is based on the arguments -
	// which will tell how many nodes that will be necessary to generate.
	// the nodes will be dynamically allocated, and the function doesn't have a return type as all generated
	// nodes inside the function will be pushed back into the vector that keeps track of the nodes
	// this method uses dynamic allocation for flexibility
	void NodesGenerator(int mazeWidth, int mazeHeight);
	void maze_StartEndPOS(); //gives a random start and end position of each generated maze

	std::vector<MazeNode*> findNeighboors(); //finds unvisited neighboors and returns pointers to the nodes.


	//Generates a maze using the DFS algorithm. After all nodes are generated like a 2D matrix from the method
	// 'NodeGenerator', this method creates a randomized path through the matrix from the start node 
	// to the end node using DFS. Thus this method is not responsible for node generation. 
	// Since the class holds the maze datastructure itself, this method have direct access to all its
	// members and methods (including 'the vector 'MazeNodes'), and can use it without needing to return a value.
	// The parameter is a pointer to the first starting node of the maze which is where the maze begins.
	//This method modifies the nodes, my marking them as visited/not visited, and also breaking the walls
	// between the nodes (that was created by 'WallGenerator') to create a random path to the end.
	void DFS_Generator();
	//void BFS_Generator(); //creates a maze using BFS instead of DFS




	//void linkNodes(); //method that is used to link nodes. Will be used by DFS/BFS ? 

	//method that returns pointers that will point to the beginning and end of the 2D vector/Matrix. 
	// These will be used to access all rows (and thus nodes) within the 2D matrix to link the nodes together
	// with its neighbours. They are marked as const because they will not modify the values of the nodes.
	//const std::vector<std::vector<MazeNode*>>* begin() const;
	//const std::vector<std::vector<MazeNode*>>* end() const;

	//two methods that will return pointers to beginning & end of 2D matrix. Modification allowed
	//std::vector<std::vector<MazeNode*>>* begin();
	//std::vector<std::vector<MazeNode*>>* end();

	//this method is responsible to create walls around all generated nodes from 'NodesGenerator'.
	//After the nodes are set up, and walls created between the nodes, the DFS algorithm will break walls 
	//and find a path through the maze
	void WallGenerator();

	//Getter-method that access and returns an alias/reference to the mazeVector of this current object/maze.
	// using the typedef definitin for ease of use.
	//creating a const before the return type indicates that this function will return a value that can only
	// be read, and not modified. Read access only is allowed since we do not want to modify the gernated maze.
	// by having const before the function body, we specify that this functions only purpose is to get certain
	// values of the class, and is not allowed to modify any of the values that is used in the bodies. 
	// this makes the function a const-member function. These two consts together creates a contract that
	// tells that this function can be safely called on cricical datamermbers that is not allowed to be modified.
	
	
	//typedef std::vector<std::vector<MazeNode*>> MazeVector; //might not be needed.
	
	
	using MazeVector = std::vector<std::vector<MazeNode*>>;
	
	// inside class mazeGenerator.h under the public section: 
	const MazeVector& getMazeVector() const override {return mazeVector;};






	//const std::vector<std::vector<MazeNode*>>* begin(); //pointer to beginning of maze
	//const std::vector<std::vector<MazeNode*>>* end(); //pointer to end of maze
	//const std::vector<std::vector<MazeNode*>>* startPos; //pointer to access start node of maze
	//const std::vector<std::vector<MazeNode*>>* endPos; //pointer to access end node
	~mazeGenerator();


private:

	
	//mazeDisplayer mazeDisplayer;

	int option = 0; //default value == 0, which iniatiates the default ctr (kolla om verkligen behövs)

	//dimensions of the maze. These dimensions will then be used to generate nodes, and also to generate walls
	// and to generatet start & end position of the maze.
	int mazeWidth;
	int mazeHeigth;
	bool wall; // true = open. False = Blocked.


	//std::vector<MazeNode*> startLine; //pointer to the line that has the start node
	//std::vector<MazeNode*> endLine; //pointer to the line that has the end node



	//the entire structure of a single node. 
	/*
	struct MazeNode {
	public:
		bool visited = false; //true or false -> sets false as default.
		bool flag = false; //a flag that will be set on each visited cell to flaga it as visited (behövs??)

		// pointers that is pointing to a neighbouring node, each direction.
		// these pointers will be used to link the nodes and also to generate walls between the nodes
		MazeNode* up;
		MazeNode* down;
		MazeNode* left;
		MazeNode* right;

		std::pair<int, int> Coordinates; //coordinates.first = x. coordinates.second = y

		//creates new node object with coordinates. The pointers is initially set to nullptr as default (why?).
		// after all nodes has been generated the pointers will be set to it's neighboors to link the nodes.
		MazeNode(std::pair<int, int> Coordinates) :Coordinates(Coordinates),
			up(nullptr), down(nullptr), left(nullptr), right(nullptr) {};

		int index = 0; // behövs? 
	};

	*/

	//pointers to start and end positions of the nodes in the maze. Will represent the beginning and end of path.
	// using pointers maakees it possible to store refeerences to specific adresses of the nodes within
	// the 2D matrix. By using pointer we can access the memory adresses and ensure that it's the right
	// nodes within the maze.
	//this makes a declaration that startNode and endNode are pointers to the struct MazeNode* inside the class
	// mazeGenerator (which is why the resolution scope operator "::" is used.
	mazeGenerator::MazeNode* startNode;
	mazeGenerator::MazeNode* endNode;
	mazeGenerator::MazeNode* currentPos; //keeps track of current position in the mazeGeneration
	int x, y; //will be used for easier coordinate reference to a node
	int generateFlag = 0; //a flag that will indicate if a maze has been generated or not.

	//MazeNode currMazeNode;

	//the stack will contain pointers to nodes. By using pointers to the node and not the nodes themselves,
	// reduce overhead of copying large amount of data. Since storing the memory addresses to the Node objects
	// takes less space than copying and saving the objects themselves, this can improve performance.
	std::stack<MazeNode*> mazeStack;

	//will contain pointers to all nodes in the entire maze. 
	//making it easy to iterate, manipulate, traverse and perform operations over all nodes in the maze.
	std::vector<MazeNode*> nodesVector; // vector with node pointers to all nodes in the maze
	std::vector<std::vector<MazeNode*>> mazeVector; //vector that holds the vector that has the pointer to all nodes


	//std::vector<std::vector<MazeNode*>> *rowPtr; //pointer to access each row.
	std::vector<int> neighbours; //vector that will be holding indices of neighbours. maybe not needed?

	std::vector<std::vector<MazeNode*>> startVec; //Not needed? 


};

#endif // !MAZE_H


