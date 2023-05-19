#include "mazeGenerator.h"

//generates 11x11 maze with DFS by defaultt.
// i & j = the coordinates of each nodes in the maze.
// for each coordinatee 'NodesGenerator' is called to create a node at that specific coordinate
mazeGenerator::mazeGenerator()
{
	printf("HELLOOOO");
	this->mazeWidth = 6;
	this->mazeHeigth = 6; 
	// Generates nodes with fixed dimensions as arg. Then pushes the nodes baack indo the 'NodesVector'
	// and then pushes the 'NodesVectors' back into the mazeVector. This function keeps the nodes 
	// unlinked, to be able later decide which nodes that should be linked to form a path and which nodes
	// that should have walls between them and not be linked.
	this->NodesGenerator(mazeWidth, mazeHeigth); 
	
	//Based on the generated nodes, this function will determine a start/end node for the maze, which will be used
	// to guide the maze generation process. Start and end pos is random
	this->maze_StartEndPOS();

	//by default, the program will generate an 11x11 maze with recursive DFS. 
	// this function will link the nodes to generate a path 
	// (and not create walls between adjacent nodes that is part of the path)
	//next step. generate path and link nodes within the path. needs to be recursive.
	this->DFS_Generator();

	//this method will generate walls between nodes that are not linked and not part of the maze path. 
	// after wall generation the maze datastructure will be complete.
	// this method will generate walls between nodes that are not connected. Thus iterate through
	// all nodes and check for connection for all nodes of the nodes - if a node has a side with no connection
	// means that there is no path, and a wall should be placed there.
	this->WallGenerator(); 
}

// this constructor lets the user generate a customized maze based on user input 
// Algorithm can have the value of 'BFS' or 'DFS', which will determine chosen algorithm to generate maze.
// if option == 2, means that the user chose to generate a default size, this condition will be asked in the body.
//If the user have not explicitly chosen 'BFS', then DFS will be used by default. If he user have not given a value
// to option, then it will be == 1 and create a default 11x11 maze with the default constructor.
mazeGenerator::mazeGenerator(int MazeWidth, int MazeHeight, int algorithm) : mazeWidth(MazeWidth), mazeHeigth(MazeHeight)
{
	this->NodesGenerator(mazeWidth, mazeHeigth); // generates nodes with fixed size from user

	
	// start_end_POS();
	if (algorithm == 0) {
		// DFS_Generator(pointer to the node with start index as parameter); 
	}
	else if (algorithm == 1) {
		//BFS_Generator();
	}

	// calls the wall generator to generate walls and also the start_end method.
	// Wallgenerator(); 
}




//return type = void since this is a method that updates the state of the class by generating nodes and 
// pusing them inside the 'nodesVector' by using the pair coordinates xC and yC. Each iteration will represent
// a different coordinate that is based on the given width and height that the user gave as input.
// the iteration start with one row and then generates nodes of each column of that row, etc. 
// After all nodes are generated and pointers to each node, we push them back to the mazeVector,
// Which is a 2D vector, that will create a 2D matrix of all generated nodes

// The vector 'nodesVector' will have pointers to all nodes in the entire maze, where each node will have its
// own coordinates xC and Yc. When all nodes are generated, 
// the 2D vector 'mazeVector', will contain vectors that points to all respective maze rows,
// after each row has been assigned in the 'NodesVector', that row will be pushes back into 'mazeVector'
// so each element in the 'mazeVector' will represent a row inside the maze

// x = rows, y = columns
void mazeGenerator::NodesGenerator(int mazeWidth, int mazeHeight)
{
	// Xc = X coordinate, Yc = Y coordinate
	for (int xC = 0; xC < mazeHeight; xC++) {
		for (int yC = 0; yC < mazeWidth; yC++) {
			std::pair<int, int>Coordinates = std::make_pair(xC, yC); //makes a pair of the coordinates
			MazeNode* nodePtr = new MazeNode(Coordinates); //creates new node with coordinates & a pointer to it
			this->nodesVector.push_back(nodePtr); //pushes the nodePtr to the nodesVector
		}
		this->mazeVector.push_back(nodesVector); //add nodesvector into mazeVector to create the 2D matrix
	}	

	//after node generation is complete start and end position of the maze will be generated.
	this->maze_StartEndPOS();
}

void mazeGenerator::maze_StartEndPOS()
{

	//line will hold a random value between n-1 where n = 4 in this case, which represents the 4 different
	// edges where the start and end position can be inside the maze. rand () will give a random integer 
	// between 0 and rand_max, and ' % 4 ' makes sure to compute the output of rand () with modulo 4,
	// this ensures the output of the whole rhs expression to be between 4-1 (3) and 0. Which represents 4 lines
	//std::vector<MazeNode*> startLine; //pointer to the line that has the start node
	//std::vector<MazeNode*> endLine; //pointer to the line that has the end node

	int  line = rand() % 4; // 0 = up, 1 = left, 2 = down, 3 = right

	// kan ja använda mig av copy ctr här kanske? alternativt, move ctr? move assign?
	// kanske copy ctr med referens ?
	// jag vill att startLine och endLine ska vara referens till de korrekta raderna i 2D-matrisen.!!
	// på så sätt, så kommer de vara referenser till de rätta noderna och elementen i mazen, och sedan väljs
	// startposition och slutposition ut av dessa valda rader. Får fixa.

	switch (line) {
	case 0: // up = startLine (first row)
		//startNode will point to a random node of the upper/first row of the 2D vector "mazeVector"
		//endnode will point to a random node of the opposite/lower side of the maze and declare it as endnode
		//for the maze
		this->startNode = mazeVector[0][rand() % mazeWidth]; //random node upper row
		this->endNode = mazeVector[mazeHeigth - 1][rand() % mazeWidth]; //random node lowest row

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
		std::cout << "something went wrong .. ? ";
		break;
	}

}

std::vector<mazeGenerator::MazeNode*> mazeGenerator::findNeighboors()
{
	//MazeNode* ptr = this->mazeStack.top();
	std::vector<MazeNode*> foundNeighboors;

	//sets x and y to the coordinates of the current position (top stack node)
	//int x = this->currentPos->Coordinates.first; //makes the ifstatements shorter and more readable.
	//int y = this->currentPos->Coordinates.second;

	//foundNeighboors.push_back(mazeStack.top());

	//Ensures that both the x and y coordinate is within the matrix boundaries
	if (x >= 0 && x <= this->mazeHeigth - 1 && y >= 0 && y <= mazeWidth - 1) {

		//check left
		
		//if the coordinate above is within the boundaries of the matrix, if true there is a neighbor there.
		// if not visited: the pointer to that specific not will be pushes back into foundNeighbours,
		// so the vector "foundNeighbours" will contain pointers to the nodes inside the mazeVector 
		// (2D matrix), and so, by pushing back a pointer that points to that specific coordinate, we can use
		// that pointer to access the right element and coordinate inside the 2D matrix/mazeVector
		if (x - 1 >= 0 && mazeVector[x-1][y]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x-1][y]); //pushes back nodepointer to the vector
		}

		//column right
		if (y + 1 <= mazeWidth - 1 && mazeVector[x][y + 1]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x][y + 1]);
		}

		//row down
		if (x + 1 <= mazeHeigth - 1 && mazeVector[x + 1][y]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x + 1][y]);
		}

		//column left
		if (y - 1 >= 0 && mazeVector[x][y - 1]->getVisited() == false) {
			foundNeighboors.push_back(mazeVector[x][y - 1]);
		}
	}

	// return vector with pointers to unvisited neighbors
	return foundNeighboors;
}

void mazeGenerator::DFS_Generator()
{
	//if generateFlag == 0, means that this is the first time that the maze is being generated and that
	// the start  values should be set. THis makes sure that the startNode is only set once regardles of how 
	// many times the function is recursively called.
	if (this->generateFlag == 0) {
		this->startNode->setVisited(true); //sets the startNode as visited by default.
		this->mazeStack.push(this->startNode); //pushes the first startnode into the stack.
		this->generateFlag = 1;
	}
	//while(mazeStack.notempty() <-- while loop that will iterate and recursibely call the DFS function until the
	//stack is empty. When its empty means that we have reached the endNode. its important to visit all nodes in
	// the stack, to make sure that there might be possible paths that can lead to the end node, making the maze
	//more complex.

	// if the mazeStack is not empty: 
	if (!this->mazeStack.empty()) {
		
		//makes sure that the current pointed out position is always the node at the top of the stack
		this->currentPos = mazeStack.top();
		
		//makes sure that x and y will represent the coordinates of the current top stack node (for easier read)
		this->x = currentPos->getCoordinatesFirst(); //sets the x value to the first node coordinate
		this->y = currentPos->getCoordinatesSecond(); // sets y to the second node coordinate
		
		//this->x = this->currentPos->Coordinates.first; 
		//this->y = this->currentPos->Coordinates.second;

		std::vector<MazeNode*> foundNeighboors = findNeighboors(); //returns unvisited neighbors

		//if foundNeighboors returned unvisited nodes 
		if (!foundNeighboors.empty()) {

			//mazeDirection will be a pointer to one of the nodes pointed by foundNeighbors.
			// the path will be determined by a random value based on how many nodepointers inside foundNeighbours
			// essentially: mazeDirection will point to the same node as one of the pointers inside foundNeighbours
			MazeNode* mazeDirection = foundNeighboors[rand() % foundNeighboors.size()];

			mazeStack.push(mazeDirection); //pushes the new visited node to the top of the stack
			mazeDirection->setVisited(true); //sets new top stack node to visited
			//mazeDirection->visited = true; //sets to visited
			
			//if mazeDirection = pointer to the node up
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

		// no unvisited neighboors, starts to backtrack and pop the top node of the stack.
		else {
			mazeStack.pop(); 
		}
		this->DFS_Generator(); //recursively calls the function to examine next node.
	}

	//stack is empty means all nodes have been searched and popped and maze is complete.
	else {
		std::cout << "starting printFunction";
	}
	//starts class displayMaze, pass over the datastructure of the maze and print it out.
}

//oid mazeGenerator::BFS_Generator()
//{

//}



// KAN NOG TA BORT LINK NODES

//links all the nodes together that have been generated by the function 'NodesGenerator'
// this functions responsibility is to create link betwween all nodes.

/*
void mazeGenerator::linkNodes()
{

		//iterates through all nodes inside the nodesvector. 'node' is a reference to the nodepointers.
		// this ranged based foor loop iterates through all pointers inside the nodesVector, where all pointers
		// point to a specific node. For each node there will be an examination if left, right, up and down
		// is within the boundaries, if true -> then a link is generated to connect the potential neighbours.
		for (auto& node : this->nodesVector) {
			
			//checks if the node has left neighboor. If one step left of the node is within the boundaries 
			//of the matrix means that there is a node and thus neighbour there
			if (node->Coordinates.first - 1 > 0) {
				MazeNode* leftNode = this->mazeVector[node->Coordinates.first - 1][node->Coordinates.second];
				//node is a pointer to the current node. the left pointer of the current node is now pointing
				// to the node at the right position. LeftNode is a pointer to the node left of 'node', and it's
				// right pointer is now pointing to the current node. this is how the linking is done
				node->left = leftNode; 
				leftNode->right = node;
			}

			//checks if the node has a right neighbour. If one step to the right of the node is less than the
			// with of the row, means that there is a node to the right
			if (node->Coordinates.first + 1 < this->mazeWidth) {
				MazeNode* rightNode = this->mazeVector[node->Coordinates.first + 1][node->Coordinates.second];
				node->right = rightNode;
				rightNode->left = node;
			}

			//if there is a neighbour one step over the node
			if (node->Coordinates.second - 1 > 0) {
				MazeNode* upNode = this->mazeVector[node->Coordinates.first][node->Coordinates.second-1];
				node->up = upNode;
				upNode->down = node;
			}

			//if there is neighbour below
			if (node->Coordinates.second + 1 < mazeHeigth) {
				MazeNode* downNode = this->mazeVector[node->Coordinates.first][node->Coordinates.second + 1];
				node->down = downNode;
				downNode->up = node;
			}
		}
}
*/

/*
//returns pointer to the beginning of the 2D matrix/mazeVector
const auto* mazeGenerator::begin() const
{
	return mazeVector.data();
}
//returns vector to the end of the 2D matrix. mazeVector.data() adress of the first element
// mazeVector.size() = number of elements. Together .data + .size() = the last element of the vector
const auto* mazeGenerator::end() const
{
	return mazeVector.data() + mazeVector.size();
}*/




//iterates through all nodes, and creates walls between each node.
void mazeGenerator::WallGenerator()
{

}

//typedef mazeGenerator::MazeVector MazeVector;
//Getter -> returns a reference to the mazeVector. Making it const because this function should not have any 
//priveledge to change or modify values, only return values
//typedef mazeGenerator::MazeNode MazeNode;

//const std::vector<std::vector<mazeGenerator::MazeNode*>>& mazeGenerator::getMazeVector() const
//{
	//return this->mazeVector;
//}
//typedef  std::vector<std::vector<mazeGenerator::MazeNode*>> MazeVector;
//const std::vector<std::vector<mazeGenerator::MazeNode*>>& mazeGenerator::getMazeVector() const
//{
	//return this->mazeVector;
//}

mazeGenerator::~mazeGenerator()
{
	//range based forloop that deletes all dynamically allocated nodes in the heap - frees up the memory
	for (MazeNode* node : nodesVector) {
		delete node;
	}
}

