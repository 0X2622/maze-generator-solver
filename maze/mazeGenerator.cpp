#include "mazeGenerator.h"
#include <cstdlib>  // used for srand() and rand()
#include <ctime>    // used for time()

//default ctr that sets the matrix dimensions, call the node generator with the given dimensions, sets the maze start
// and maze end positions and lastly creates a DFS maze path based on these previous generated data structures.
mazeGenerator::mazeGenerator() : mazeWidth(6), mazeHeigth(6)
{
	this->NodesGenerator(mazeWidth, mazeHeigth); 
	this->maze_StartEndPOS();
	this->DFS_Generator();
}

mazeGenerator::mazeGenerator(int MazeWidth, int MazeHeight) : mazeWidth(MazeWidth), mazeHeigth(MazeHeight)
{
	this->NodesGenerator(mazeWidth, mazeHeigth);
	this->maze_StartEndPOS();
	this->DFS_Generator();
}

// This function creates the entire datastructure of maze by creating all mazeRows and all nodes inside it
// Each induvidual mazeRow will be represented as a vector that holds pointers to created mazeNodes,
// Every generated mazeRow-vector will be pushed into the outer 2D vector 'mazeVector' which represents the maze.
// mazeWidth and mazeHeight makes sure that the dimensions (amount of mazeRows) are correct,
// the outer vector can be seen as amount of mazeRows, and the inner vector can be seen as the amount of nodes (columns)
void mazeGenerator::NodesGenerator(int mazeWidth, int mazeHeight)
{
	//the outer iteration makes sure that we create the right amount of row-vectors.
	//the nested loop make sure that we create enough nodes (columns) for each row-vector
	for (int xC = 0; xC < mazeHeight; xC++) { 
		std::vector<MazeNode*> mazeRow; // creates the Row-vector or nodePointers
		for (int yC = 0; yC < mazeWidth; yC++) {//every iteration equals to the construction of one node & pointer
			std::pair<int, int>Coordinates = std::make_pair(xC, yC); //node coordinates of the iteration values
			MazeNode* const nodePtr = new MazeNode(Coordinates); //dynamically allocates a node and a pointer
			mazeRow.push_back(nodePtr); //pushes the nodePtr to the Row-vector
		}
		this->mazeVector.push_back(mazeRow); //Pushes the Row-vector to the 2D mazeVector
	}	
}

//sets the start and end-nodes for the matrix. The nodes will be at opposite sides/walls but at a random position on the
//walls. rand() together with srand() will be used to generate a random number between 0 and 3, which will determine
//which walls to set the start and end-node. once a wall is chosen, rand() will be used again to set a random position
//within that wall, both for the start and end-nodes - resulting in two random positions.
void mazeGenerator::maze_StartEndPOS()
{



	// source " https://cplusplus.com/reference/cstdlib/srand/ " 
	// time() https://cplusplus.com/reference/ctime/time/
	// source: srand and rand() https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
	
	// time() access the time in the computer. time(0) access the current time in second as an integer. 
	// srand() is used to seed the pseudo-random number generator used by rand(), 
	//to make sure that the numbers from rand() appear more random, we need to give it a different seed to each run.
	// seed(time(0)) makes sure that the seed giving to rand is the current time on the system which will be different 
	// for each excecution. making rand() appear more rand, and the start/end point of the maze more random as well.
	std::srand(std::time(0));

	// 'rand()' returns a pseudo-random number in the range of [0, RAND_MAX], 'rand() % N' returns a number between [0, N-1],
	// because 'rand() % N' means the remainder of the number given by 'rand()' divided by N which is always < N
	// so rand() % 4 means a number X MOD 4 = Y such that Y = 0, 1, 2, or 3 which represents one of the 4 maze walls
	int line = rand() % 4;  

	//each case represnt one of the outer walls which will determine positions of the start and end-node
	switch (line) {
	case 0: // up = startLine (first row)
		this->startNode = mazeVector[0][rand() % mazeWidth]; //random column for the upper row
		this->endNode = mazeVector[mazeHeigth - 1][rand() % mazeWidth]; //random column for the bottom row
		break;
	case 1: // left = startLine (first column)
		this->startNode = mazeVector[rand() % mazeHeigth][0]; //random node leftest col
		this->endNode = mazeVector[rand() % mazeHeigth][mazeWidth - 1]; //random node rightest col
		break;
	case 2: // down = startLine (last row)
		this->startNode = mazeVector[mazeHeigth - 1][rand() % mazeWidth]; //random node lowest row
		this->endNode = mazeVector[0][rand() % mazeWidth]; //random node uppest row

		break;
	case 3: // right = startLine (last column)
		this->startNode = mazeVector[rand() % mazeHeigth][mazeWidth - 1]; //random node rightest col
		this->endNode = mazeVector[rand() % mazeHeigth][0]; //random node leftest col
		break;
	default:
		break;
	}
	//after the start & end node is set, it's important to explicitly set their node type which will be used for printing
	this->startNode->setNodeType(NodeType::START);
	this->endNode->setNodeType(NodeType::END);
}


//examines if a particular node with coordinate (x,y) har unvisited neighboors. First it checks if a particular
// node (neighbor) is within the maze boundaries - if true then it will examine if it has been visited or not. 
// if visited -> push a pointer to the node into a vector that holds pointers to unvisited nodes (neighbors)
// return value = the vector. These neighbours will be potential new paths for the DFS algorithm to traverse.
std::vector<MazeNode*> mazeGenerator::findNeighboors()
{
	std::vector<MazeNode*> foundNeighboors; //create a new vector to store pointers to potential unvisited neighboors 
		
		//up check:
		//if the position above (x,y) is within the maze boundaire (and thus have a node) and if the node at that position
		// is not yet visited:
		if (x - 1 >= 0 && mazeVector[x-1][y]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x-1][y]); //pushes back nodepointer to the vector
		}

		//right check:
		if (y + 1 <= mazeWidth - 1 && mazeVector[x][y + 1]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x][y + 1]);
		}

		//down check:
		if (x + 1 <= mazeHeigth - 1 && mazeVector[x + 1][y]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x + 1][y]);
		}

		//left check: 
		if (y - 1 >= 0 && mazeVector[x][y - 1]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x][y - 1]);
		}

	// return the vector with pointers to unvisited neighbors
	return foundNeighboors;
}

// Recursive DFS-algorithm that takes the existing 2D-matrix (with all generated nodes) and transforms it to a real maze
// This is done by creating links between adjacent nodes - where a link between two nodes will represent a path in the maze.
// Each resursive call = traversing to an unvisited neighbor (node) and creating a link (path) in the traversing direction.
// if no unvisited neighbors found = backtracking to the previous node by popping the top of the stack.
// empty stack = maze generation done, and that all nodes have been traversed and linked to an adjacent neighbor
void mazeGenerator::DFS_Generator()
{
	
	// this guard is needed because of the recursive nature of this DFS-algorithm, ensuring that the startNode is only
	// pushed into the stack top once - during the first iteration only. 
	// if startNode.visited == false, implies that the startNode has not been visited & that its the first iteration.
	// if startNode.visited == true, implies it's not the first iteration and that the startNode does not need any handling.
	if (this->startNode->getVisited() == false) {
		this->mazeStack.push(this->startNode); //pushes the first startnode into the stack.
		this->startNode->setVisited(true); //sets the startNode as visited by default.
	}

	// a guard to check whether the maze-generation is done or not. empty stack means that all nodes have been 
	// traversed, and popped, and that the generation is complete. If stack is not empty means that there are still paths
	// that needs to be analyzed and that the algorithm should keep iterating.
	if (!this->mazeStack.empty()) {
		
		//pointer that keeps track of the last visited node.
		// This pointer is used for referencing the last position when linking the node to a new adjacent neighbor
		this->currentPos = mazeStack.top();
		
		//for easier read, x & y = coordinates of the top stack node
		this->x = currentPos->getCoordinatesFirst(); 
		this->y = currentPos->getCoordinatesSecond(); 
		std::vector<MazeNode*> foundNeighboors = findNeighboors(); //returns a vector of unvisited neighbors to visit

		//If unvisited neighboors = found -> randomly traverse to one of the neighboors and link it with current node,
		// no unvisited neighbor = pop stack + backtrack
		if (!foundNeighboors.empty()) {

			//foundNeighboors is a vector that holds pointers to potential neighbors to visit. 
			// mazeDirection will be pointing to one of the available neighbors. The choice of neighbor will be random.
			MazeNode* mazeDirection = foundNeighboors[rand() % foundNeighboors.size()];
			mazeStack.push(mazeDirection); //pushes the newest visited nodepointer to the top of stack 
			mazeDirection->setVisited(true); //mark that node as visited since its at the top of the stack.
			this->linkNodes(mazeDirection, currentPos);
		}
		else {
			mazeStack.pop();  // no unvisited neighboors, starts to backtrack and pop the top node of the stack.
		}
		this->DFS_Generator(); //recursively calls the function to examine next node.
	}
}

//section below handles the linking process between the new node pointed by mazeDirection and the previous node
// pointed by currentPos. To be able to link the correct nodes, the coordinates of the newly visited nodes has
// to be retrieved. To retrieve the coordinates of the newly visited node, we use the getter function
// "getCoordinatesFirst" and "getCoordinatesSecond", where each of these getter functions will return one 
// of the node coordinates of a particular node. In this case, that particular node is the node pointed by 
// mazeDirection, which is the newly visited node. After the coordinates are retrieved by the getters, we check
// where those coordinates are located from the perspective of the current (previous) node pointed by
//currentPos. So x and y in these conditions will represent the node coordinates of the node pointed by 
// currentPos, and thet statements checks where the newly visited node are located from the perspective of that
// node.

// this function link together two adjacent mazeNodes to create a path in the maze.
// the nodes that are to be linked are the top 2 stack nodes (latest visited nodes),
// two mazeNode pointers are passed as reference to avoid copying and save overhead.
// the arguments (pointers) are also marked as "const" since they are not to be changed by the function.
// the only change is done on the objects (nodes) pointed at, and not the Node-pointers. 
void mazeGenerator::linkNodes(MazeNode*& const mazeDirection, MazeNode*& const currentPos)
{
	//x and y will be at this point coordinates to the second top node (pointed by currentPos),
	// and these if-statements will examine the coordinates of the node pointed by mazeDirection from the perspective
	// of the node point by currentPos.
	//if mazeDirection = pointer to the node above:
	if (mazeDirection->getCoordinatesFirst() == x - 1 && mazeDirection->getCoordinatesSecond() == y) {

		//links the previous node (that is pointed by currentPos) and the new node pointed by mazeDirection
		mazeDirection->setDownPtr(currentPos);
		currentPos->setUpPtr(mazeDirection);
	}

	//right
	else if (mazeDirection->getCoordinatesFirst() == x && mazeDirection->getCoordinatesSecond() == y + 1) {
		mazeDirection->setLeftPtr(currentPos);
		currentPos->setRightPtr(mazeDirection);
	}

	//down
	else if (mazeDirection->getCoordinatesFirst() == x + 1 && mazeDirection->getCoordinatesSecond() == y) {
		mazeDirection->setUpPtr(currentPos);
		currentPos->setDownPtr(mazeDirection);
	}

	//left
	else if (mazeDirection->getCoordinatesFirst() == x && mazeDirection->getCoordinatesSecond() == y - 1) {
		mazeDirection->setRightPtr(currentPos);
		currentPos->setLeftPtr(mazeDirection);
	}
}

//getter function to return the mazeVector. This function is used by external classes to access the maze Datastructure
//and pass it around to other objects as a first class citizen. Const makes sure the data is not modifiable.
const std::vector<std::vector<MazeNode*>>& mazeGenerator::getMazeVector() const
{
	return this->mazeVector;
}

//destructor. Since this class dynamically allocate mazenodes, they need to explicitly be deleted from the heap memory
//when the object gets destroyed to avoid memory leaks. So everytime that the destructor is called, it uses a 
// range based for loop, that iretares through all generated nodes in the mazeVector, and deletes them, after all nodes
// for an entire row has been deleted, then that row vector will get cleared,
// once all row vectors has been cleared, then the entire mazeVector can be cleared. OBS Check if cleared is necessary.
mazeGenerator::~mazeGenerator()
{
	for (auto& mazeRow : this->mazeVector) { //fetches vectors that hold entire mazeRows.
		for (auto& node : mazeRow) { //iterates through all nodes in the entire fetched fector
			delete node; // Deallocates the memory for the node
		}
		mazeRow.clear(); // Clear the vector for this row once all nodes are deleted (maybe i can delete this shit?)
	}
	this->mazeVector.clear(); // Clear the outer vector
}

