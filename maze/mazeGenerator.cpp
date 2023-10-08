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
	
	// srand is needed to give the rand() function a seed that will make it appear more random,
	// this is important to make sure that the node start and end position is more random. 
	// time(0) gives the current time in the computer as an integer, which makes the seed different each time.
	std::srand(std::time(0));
	
	// returns a pseudo-random number between [0, RAND_MAX], 'rand() % 4' returns a number between [0, 3],
	// which represents one of the 4 maze walls
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
	// pushed into the stack top only once - during the first iteration only. 
	if (this->startNode->getVisited() == false) {
		this->mazeStack.push(this->startNode); //pushes the first startnode into the stack.
		this->startNode->setVisited(true); //sets the startNode as visited by default.
	}

	// a guard to check whether the maze-generation is done or not. empty stack means that all nodes have been 
	// traversed, and popped, and that the generation is complete. If stack is not empty means that there are still paths
	// that needs to be analyzed and that the algorithm should keep iterating.
	if (!this->mazeStack.empty()) {
		
		// This pointer is used for referencing the last position when linking the node to a new adjacent neighbor
		this->currentPos = mazeStack.top();
		
		//for easier read, x & y = coordinates of the top stack node
		this->x = currentPos->getCoordinatesFirst(); 
		this->y = currentPos->getCoordinatesSecond(); 
		std::vector<MazeNode*> foundNeighboors = findNeighboors(); //returns a vector of unvisited neighbors to visit

		//If unvisited neighboors == found -> randomly traverse to one of the neighboors and link it with current node,
		// no unvisited neighbor -> pop stack + backtrack
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

//destructor. Since this class dynamically allocate mazenodes, they need to explicitly be deleted from the heap
//when the object gets destroyed to avoid memory leaks. 
mazeGenerator::~mazeGenerator()
{
	for (std::vector<MazeNode*>& mazeRow : this->mazeVector) { //fetches vectors that hold entire mazeRows.
		for (MazeNode *& node : mazeRow) { //iterates through all nodes in the entire fetched fector
			delete node; // Deallocates the memory for the node
		}
	}
}

