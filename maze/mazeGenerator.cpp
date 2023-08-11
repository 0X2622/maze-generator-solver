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

//Dynamically allocate mazenodes, and sets pointers to all dynamically allocated nodes.
// the nodes are given coordinates Xc and Yc as parameters. The coordinates are based on the iteration of the loops,
// so every iteration of the loops will represent two values which will represent an existing coordinate inside the maze
// the coordinates are made as a pair for ease of access in the stack. Every node is initially set as a "regular" node type,
//and then at another method 2 of these nodes will be set as "start" and "end" node.
//the vector "mazeRow" is a vector that represents an entire row in the maze, for every generated node, that node will
// get pushed into mazeRow. Once mazeRow have nodes for a complete row, then that entire row will get pushed into
// the real matrix structure "mazeVector", which will contain multiple vector of mazeRows. Which is why we create a new 
// vector mazeRow for every new row that we want to allocate nodes to, since that vector will represent an entire new row.
//once xC is equal to the value of mazeHeight, means that we have generated sufficent mazeNodes for all mazerows, which
//is the flag that the allocation can stop.
//Every generated node, will have a pointer pointing towards it for ease of access and manipulation.
void mazeGenerator::NodesGenerator(int mazeWidth, int mazeHeight)
{
	this->mazeVector.clear(); //makes sure to clear any potential previous nodes inside the vector before generating a new
	for (int xC = 0; xC < mazeHeight; xC++) { //once we have allocated vectors for all maze rows the iteration can stop
		std::vector<MazeNode*> mazeRow; // vector that will hold node pointers to an entire matrix row
		for (int yC = 0; yC < mazeWidth; yC++) { //this loop allocated nodes and pointers to an entire maze row
			std::pair<int, int>Coordinates = std::make_pair(xC, yC); //iteration values will represent node coordinates.
			MazeNode* nodePtr = new MazeNode(Coordinates); //dynamically create a node with a pointer pointing towards it.
			mazeRow.push_back(nodePtr); //pushes the nodePtr to the nodesVector
		}
		this->mazeVector.push_back(mazeRow); //add nodesvector into mazeVector to create the 2D matrix
	}	
}

//Sets 2 of the generated nodes as "start" and "end" nodes. Start node means from where the maze start position is, etc.
//By using a random number between 0-3, where each of these 4 numbers represent a unique outer row/column, we can effectvely
//generate 2 random positions each time a maze is generated. Once the start row/column is decided, another
//random generator is used for that specific row/column, to make sure that a truly random node is chosen. 
//so this method uses 2 random functions in total, one for generating a random row/column, and then to generate a random
// node within that row/column, its also set that the end node, is going to be on the opposite side of the start node,
// this makes the mazes more complex and interesting.
void mazeGenerator::maze_StartEndPOS()
{

	// srand() is used to seed the pseudo-random number generator used by rand().
	// By providing the current time as the seed (time(0)), we ensure a different starting 
	// point in the sequence of numbers that rand() will output with each execution of the program. 
	// This makes the output of rand() appear truly random for each run with different start/end positions.
	std::srand(std::time(0));  // source " https://cplusplus.com/reference/cstdlib/srand/ " 

	// rand() generates a pseudo-random number between 0 and RAND_MAX, which will be affected by the seed.
	// The '%' operator is used to get the remainder of the division of that number by 4. 
	// which  will always return a number between 0 and 3, corresponding to four different directions.
	int line = rand() % 4;  // //soure: " https://cplusplus.com/reference/cstdlib/rand/  "



	//based on the value of "line", will initate a dfferent case, where each case will set the start and end node
	//at a random position on one of the outer edges. The end node will always be set at the opposite edge as
	// the startnode.
	switch (line) {
	case 0: // up = startLine (first row)
		//startNode (which is a node Ptr) will point to a random node of the upper row of the mazeVector,
		//endnode will point to a random node of the opposite/lower side of the maze and declare it as endnode
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

//this method is used together with the DFS algorhtm, and examines if a particular node has unvisited neighboors,
//Every node that has been visited, will be marked as "visited", and thus, by checking first if certain coordinates are
//within the matrix boundaries, and if true -> then check if the node at that position is marked as visited, or not.
//if node.visited == false, a pointer to that node is pushed back into the vector "foundNeighboors", which will contian
// pointers to found unvisited neighbors, this vector will at maximum contain 4 unvisited neighboors in the case that
// all directions where unvisited, and then the DFS method can continue its algorithm towards any of these directions
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

//This function uses recursive DFS to create a maze within the generated 2D matrix.
// It works by setting the start node as visited, pushes it into the stack, and then start the actual DFS algorithm.
// The algorithm works by exploring unvisited neighbors from the perspective of the current top stack node (currentPos),
// The unvisited neighboors are found by using the function "unvisitedNeighbors", which returns a vector of pointers
// too the neighbors. The DFS algorithm will randomly choose one of the unvisited neighboors to visit, it pushes that
// new node into the stack, sets it as "visited", and make sure to link that node with the previous node (currentPos),
// the linking is done from the perspective of both nodes. From that point the algorithm will reursively call itself
// again to do the same process again but from the perspective of the new top stack node.
// if no unvisited neighbors are found from a particular nodes perspective, then that node will be popped from the 
// stack and backtracks to the new top stack node, and check for unvisited neighboors from that stacks perspective,
// if still no unvisited neighbors are found, the backtracking continues. until there are no more unvisited neighbors.
// if there are no more unvisited neighboors, means that all nodes have been traversed and visited and that the 
// maze generation is done.
void mazeGenerator::DFS_Generator()
{
	//if generateFlag == 0, means this is the first time that the maze is being generated, and that
	// the start node should then be set as visited. This condition + the flag makes sure that the start node is only set as
	// visited and pushed into the top stack once, avoiding maze generation mistakes for future recursive calls.
	if (this->generateFlag == 0) {
		this->startNode->setVisited(true); //sets the startNode as visited by default.
		this->mazeStack.push(this->startNode); //pushes the first startnode into the stack.
		this->generateFlag = 1;
	}

	//Condition to check if the algorithm should keep iterating, or if it is done and has visited all nodes in the matrix.
	//if mazeStack = !empty this will return true and continue the algorithm. if !empty=false, means that the stack
	// is empty and that the algorithm is done.
	if (!this->mazeStack.empty()) {
		
		//pointer that keeps constant track of the current top stack node that is being analyzed. 
		// This pointer is used for easy referencing the current position when linking nodes with neighbors.
		this->currentPos = mazeStack.top();
		
		//for easier read/shorter name referencing, x & y = coordinates of the current top stack node
		this->x = currentPos->getCoordinatesFirst(); //sets the x value to the first node coordinate
		this->y = currentPos->getCoordinatesSecond(); // sets y to the second node coordinate
		std::vector<MazeNode*> foundNeighboors = findNeighboors(); //returns unvisited neighbors

		//If unvisited neighboors = found = randomly choose one of the neighboors and link it with current node,
		// no unvisited neighbor = pop stack + backtrack
		if (!foundNeighboors.empty()) {

			//RHS will return a pointer to one of the unvisited nodes, mazeDirection is set to point to the same node,
			// by setting mazeDirection to point to the same random node, we can use it to access and reference the node,
			// push it into the stack, set the node as visited, and link it with the previous node (pointed by currentPos)
			MazeNode* mazeDirection = foundNeighboors[rand() % foundNeighboors.size()];

			mazeStack.push(mazeDirection); //pushes the newest visited nodepointer to the top of stack 
			mazeDirection->setVisited(true); //mark that node as visited.
			
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
		else {
			mazeStack.pop();  // no unvisited neighboors, starts to backtrack and pop the top node of the stack.
		}
		this->DFS_Generator(); //recursively calls the function to examine next node.
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

