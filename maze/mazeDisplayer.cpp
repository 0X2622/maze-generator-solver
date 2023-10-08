#include "mazeDisplayer.h"
#include "mazeGenerator.h"
#include "ScreenManipulation.h"
#include <thread> //sleep functionality during mazesolving. Reference: https://en.cppreference.com/w/cpp/thread/sleep_for


//ctr that initalizes the class members and also start the functions to generate the matrix and the maze
mazeDisplayer::mazeDisplayer(const std::vector<std::vector<MazeNode*>>& mazeVec) : mazeVec(mazeVec)
{
    this->mazeHeight = mazeVec.size(); //sets mazeHeight to the amount of mazeRows
    this->mazeWidth = mazeVec[0].size(); //sets the mazeWidth to the mount of columns for the first mazeRow
    printMatrix(); //only prints the 2D matrix datastructure
    printMaze(); //prints the generatez maze with it's path
    DFS_MazeSolver();
}


// prints the 2D matrix structure with all cells, nodes & walls.
// The purpose to give a clear representation of the complete 2D matrix structure with start and end points
void mazeDisplayer::printMatrix(){
    this->context = "printMatrix"; //value to determine behaviour of "printMazeRow"
    this->printHorisontalWall(); //print a long horrizontal wall along the top of the matrix to create a "roof"

    // This iteration will go through all elements inside mazeVec, where each element is a vector of nodes
    // in other words - each element is a mazeRow, for each mazeRow -> print the mazeRows a long with its walls.
    for (const std::vector<MazeNode*> &mazeRow : mazeVec) {
        printRow(mazeRow); // Function that prints a visual row of nodes and it's paths/walls
        printHorisontalWall(); //after each row of printed nodes a horrizontal wall is placed beneath the row sfor sepparation.
    }
    std::cout << "Press any key to continue with the maze Generation.";
    ScreenManipulation::pressAnyKey(); //flushes the cin-buffer and then calls a cin.get() to wait for user input
    ScreenManipulation::ClearScreen(); //after user has pressed any key then the screen will be cleared for mazeGeneration
}

// Function that prints the real maze, with real paths and walls from start to the end
// This function works similar as print matrix by analyzing each element of the mazeVec, but with the
// modification that it will analyze the pointers of each node to determine if there should be a wall or path.
void mazeDisplayer::printMaze()
{
    this->context = "printMaze"; //sets the context/state of the program.
    this->printHorisontalWall(); //print a long horrizontal wall at the top of the matrix to create a "roof"

    // For each maze row, print the respective nodes, analyze their pointers and print wall/or path, do it for all rows.
    for (const std::vector<MazeNode*> &mazeRow : mazeVec) {
        printRow(mazeRow); //prints out nodes for a row and analyzes its right pointers
        analyzeDownPtr(mazeRow); //analyzes the whole same row again for its down pointers for horizontal walls/paths
        std::cout << "\n"; // Move output cursor down to next line for processing the next row.
    }
    std::cout << "Press any key + enter to solve the generated maze";
    ScreenManipulation::pressAnyKey();
}

// This function prints one horizontal wall over an entire row
// A wall is made of chunks of "------" that is placed next to each other to create the entire wall
void mazeDisplayer::printHorisontalWall()
{
    // Each induvidual iteration equals to printing a chunk of the wall which has the width of a cell 
    std::cout << " "; // Adds an extra space at the start of the line to nudge the horrizontal wall in right position
    for (int j = 0; j < mazeWidth; j++) { //print out a horrizontal wall until end of the row
        std::cout << Hori_wall; // 1 chunk of horrizontal wall = the same space of 1 cell
    }
    std::cout << "-"; //adds one extra wall unit at the right to tighten a visible gap at the end of the row
    std::cout << "\n"; //moves the output cursor down to next line for next row output
}


//function that insert nodes for a complete row. It analyzes the nodeType and outputs it. 
// Depending on the context/state this function will either just print walls after each node
// or it will examine the right node pointers to generate the maze and create walls/paths.
void mazeDisplayer::printRow(const std::vector<MazeNode*>& mazeRow){

    std::cout << Vert_wall; //Creates a vertcal wall at the left most column before each iteration
    
    // mazeNode is a reference to a node pointer inside vector mazerow, by using a reference we avoid copying and overhead,
    // this reference is const since these Node-pointers are not to be modified
    //analyzes nodeTypes for a complete row in the maze
    for (MazeNode* const &mazeNode : mazeRow) { //for each element in a mazeRow = a single mazeNode.
        
        mazeNode->setVisited(false); //sets the visited flag of all nodes to false for the MazeSolver.
       
        switch (mazeNode->getNodeType()) {
        case NodeType::START: {
            std::cout << start;
            this->StartNode = mazeNode; //sets pointer to the startNode to mark the position (for maze solveing)
            ScreenManipulation::SaveCursorPos();
            break; 
        }
        case NodeType::END: {
            std::cout << end;
            this->EndNode = mazeNode; //sets pointer to the endNode to mark the position (for maze solving)
            break; 
        }
        case NodeType::REGULAR: {
            if (context == "printMatrix") {
                std::cout << RegNode;
            }
            else if (context == "printMaze") {
                std::cout << "   ";
            }
            break; 
        }
        default:
            break;
        }
        
        //checks the context of the program and determine the behaivour of the function.
        if (this->context == "printMatrix") {
            std::cout << Vert_wall; //vertical wall after each node to surround all nodes with vertical walls
        }
        else if (this->context == "printMaze") {
            analyzeRightPtr(mazeNode); //if context is to print the maze -> analyze the right pointers for links
        }
    }
    std::cout << "\n"; // End of the node row. This causes output to go to the beginning of next line.
}

//analyzes the right pointer of a specific node. depending if the pointer has a defined link/path or not,
// this function will print a vertical path, or a vertical wall. The input is one single MazeNode
void mazeDisplayer::analyzeRightPtr(MazeNode* mazeNode)
{
    //checks whether the current nodes right pointer is linked to another node or not.
    if (mazeNode->getRightPtr() != nullptr) { // if linked print vertical path : 
        std::cout << V_path; // prints vertical path
    }
    else {
        std::cout << Vert_wall; // print vertical wall if no link
    }
}

//Takes a row as argument and analyzes the downlink/down pointers of every node of that row to determine
//if there should be a path, or a wall at that place.
void mazeDisplayer::analyzeDownPtr(const std::vector<MazeNode*> mazeRow)
{
    std::cout << " "; // places the elements of every row one step extra to the right for symmetrical alignment 
    std::cout << "|"; //tightens the vertical gap at the leftest column and puts all vertical walls in place.
    for (MazeNode* const& mazeNode : mazeRow) { //for each node in this row: 
        if (mazeNode->getDownPtr() != nullptr) { //if downPtr != NULL = print a path :
            std::cout << H_path << "|"; //print path & also add one extra "|" to fill the vertical gap that a horrizontal path creates
        }
        else {
            std::cout << Hori_wall; // if downPtr is not linked, print a horrizontal wall instead of path.
        }
    }
}

// finds a path from StartNode to EndNode by analyzing the pointers of a node to see if there is a link (path)
// to an adjacent node. If there is a link that leads to an unvisited neighbor, then that neighbor will be set
// to the top of the stack, the tracker will be updated to the new node, and then a new link will be explored
// from the new node. The tracker will start by pointing towards the startNode, if tracker == EndNode 
// means the maze has been solved. No link &&  Nounvisited path means backtracking and popping the top of stack.
// a real time visual representation of how the tracker is analyzing and solving the maze is shown in the screen 
void mazeDisplayer::DFS_MazeSolver()
{
    //makes sure that the StartNode is only pushed once into the nodestack
    if (this->StartNode->getVisited() == false) {
        this->NodeStack.push(StartNode);
        ScreenManipulation::restorePosition(); // Restore cursor position to the marked startnode
        ScreenManipulation::smallStepLeft(); //necessary small adjustements to the left for the cursors start position
    }

    // updates the tracker to the top of stack and sets that node as visited before we analyze adjacent nodes,
    // this way, we can check if the tracker has reached the EndNode before each recursion.
    this->Tracker = NodeStack.top(); 
    Tracker->setVisited(true); 

    // As long as Tracker != EndNode && there are nodes left to be analyzed:
    if (Tracker != EndNode && !NodeStack.empty()) {

        // This section analyzes where there are potential paths to traverse,
        // potential paths are found my examining links to adjacent nodes and check if they have been visited,
        // by checking if visited == false we prevent the solver from visitng a node that has been visited
        if (Tracker->getLeftPtr() != nullptr && Tracker->getLeftPtr()->getVisited() == false) {
            std::cout << MazePathLeft;
            ScreenManipulation::StepLeft(); //moves the cursor towards the step direction.
            NodeStack.push(Tracker->getLeftPtr()); //pushes the node left of the tracker to the stack
            std::this_thread::sleep_for(std::chrono::milliseconds(170)); //sleep to se the solver in real-time
        }
        else if (Tracker->getUpPtr() != nullptr && Tracker->getUpPtr()->getVisited() == false) {
            std::cout << MazePathUp;
            ScreenManipulation::StepUp();
            NodeStack.push(Tracker->getUpPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(170));
        }
        else if (Tracker->getRightPtr() != nullptr && Tracker->getRightPtr()->getVisited() == false) {
            std::cout << MazePathRight;
            ScreenManipulation::StepRight();
            NodeStack.push(Tracker->getRightPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(170));
        }
        else if (Tracker->getDownPtr() != nullptr && Tracker->getDownPtr()->getVisited() == false) {
            std::cout << MazePathDown;
            ScreenManipulation::StepDown();
            NodeStack.push(Tracker->getDownPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(170));
        }
        else {
                // if no available paths found && tracker has not reached the EndNode -> Backtrack
                BackTrack();
                NodeStack.pop(); // pops the stack top to analyze the previous node
        } 
        DFS_MazeSolver(); //recursively calls itself
    }
    else if (Tracker == EndNode) { returnToMenu(); }
}

//this function is made for the visual represntation of the solver so it can know which direction to traverse
// when the stacked is popped and the tracker is backtracking to a previous node.
// potential links of a node will be analyzed to see where backtracking might be possible,
// if there is a link/path, and the node at that path has not been backtracked to before, then the visual
// tracker can step towards that particular direction.
void mazeDisplayer::BackTrack()
{
    // if there is a path to a node above, and that node has not yet been back tracked, means that this is the
    //next direction of the tracker after the stack has being popped, and which direction to visaully traverse,
    if (Tracker->getUpPtr() != nullptr && Tracker->getUpPtr()->GetBackTracked() == false) {
        // Move cursor up
        std::cout << MazePathUp; //prints a footstep to the direction that we can backtrack
        std::this_thread::sleep_for(std::chrono::milliseconds(170)); //sleeps the program to keep the speed
        Tracker->SetBackTracked(true); //sets the node as "backtracked" to prevent future backtracking
        ScreenManipulation::StepUp(); // make the cursor take a visual step to the back tracking direction
    }
    else if (Tracker->getDownPtr() != nullptr && Tracker->getDownPtr()->GetBackTracked() == false) {
        // Move cursor down
        std::cout << MazePathDown;
        std::this_thread::sleep_for(std::chrono::milliseconds(170));
        Tracker->SetBackTracked(true);
        ScreenManipulation::StepDown();
    }
    else if (Tracker->getLeftPtr() != nullptr && Tracker->getLeftPtr()->GetBackTracked() == false) {
        // Move cursor left
        std::cout << MazePathLeft;
        std::this_thread::sleep_for(std::chrono::milliseconds(170));
        Tracker->SetBackTracked(true);
        ScreenManipulation::StepLeft();
    }
    else if (Tracker->getRightPtr() != nullptr && Tracker->getRightPtr()->GetBackTracked() == false) {
        // Move cursor right
        std::cout << MazePathRight;
        std::this_thread::sleep_for(std::chrono::milliseconds(170));
        Tracker->SetBackTracked(true);
        ScreenManipulation::StepRight();
    }
}

//function to exit the mazesolver and return to the main menu
void mazeDisplayer::returnToMenu()
{
    ScreenManipulation::pressAnyKey();
    ScreenManipulation::ClearScreen();
    return; // Exit the function
}

//Destructor of the object
mazeDisplayer::~mazeDisplayer() {

}
