#include "mazeDisplayer.h"
#include "mazeGenerator.h"
#include <limits>


//ctr that initalizes the class members and also start the functions to generate the matrix and the maze
mazeDisplayer::mazeDisplayer(const std::vector<std::vector<MazeNode*>>& mazeVec) : mazeVec(mazeVec)
{
    printMatrix(); //only prints the 2D matrix datastructure
    printMaze(); //prints the generatez maze with it's path
}


//prints the 2D matrix structure with all nodes & walls. Purpose to give the user a clear representation
// of the complete 2D matrix with start and end points.
void mazeDisplayer::printMatrix()
{
    this->funType = "printMatrix"; //value to determine behaviour of "printRowNode"
    this->printHorisontalWall(); //print a long horrizontal wall along the top of the matrix to create a "roof"

    //for each element in mazeVec, where each element = a complete row, 6 in total. 
    //For all individual rows, print their respective nodes and walls
    for (const auto& mazeRow : mazeVec) {
        printNodeRow(mazeRow); //each iteration is equal to one complete row of printed nodes
        printHorisontalWall(); //after each row of printed nodes a horrizontal wall is placed beneath the row for sepparation.
    }

    std::cout << "Press any key to continue with the maze Generation.";
    //ignores all characters in the input buffer until new line. preventing it from being consumed by cin.get()
    //source "https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n" 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();  //now cin.get() will pause the program and wait for the user to provide a new input
    
    // "\033[2J" clears the screen and "\033[1;1H" moves the cursor to the upper left corner of the screen.
    // Which is needed for generating the actuall maze. 
    //Src : " https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code " 
    std::cout << "\033[2J\033[1;1H"; 
}

//method for printing the actuall generated maze, that will contain the continous path from the start node "S" to the
// end node "E"
void mazeDisplayer::printMaze()
{
    this->funType = "printMaze"; //sets the context/state of the program.
    this->printHorisontalWall(); //print a long horrizontal wall at the top of the matrix to create a "roof"

    // For each maze row, print the respective nodes, analyze their pointers and print wall/or path, do it for all rows.
    for (const auto& mazeRow : mazeVec) {
        printNodeRow(mazeRow); //prints out nodes for a row and analyzes its right pointers
        analyzeDownPtr(mazeRow); //analyzes the whole same row again for its down pointers for horizontal walls/paths
        std::cout << "\n"; // Move output cursor down to next line for processing the next row.
    }

    std::cout << "Press any key + enter to return to the main menu";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\033[2J\033[1;1H";
}

//purpose of function is to print a horrizontal wall over a complete matrix row to create sepparation between rows
void mazeDisplayer::printHorisontalWall()
{
    // mazeVec[0] = first vector/row in the matrix, 
    // mazeVec[0}.size = number of elements for the first row.
    std::cout << " "; // Extra space at the start of the line to make the horrizontal wall in right position
    for (int j = 0; j < mazeVec[0].size(); j++) { //print out a horrizontal wall until end of the row
        std::cout << Hori_wall; // 1 horrizontal wall = the space of 1 node
    }
    std::cout << "-"; //adds one extra wall unit at the right to tighten the gap
    std::cout << "\n"; //moves the output cursor down to next line for next row output
}


//function that insert nodes for a complete row. It analyzes the nodeType and outputs it. 
// Depending on the context/state this function will either just print walls after each node
// or it will examine the right node pinters to generate the maze and create walls/paths.
// The argument is a complete row, and a string that tells the state/context.
void mazeDisplayer::printNodeRow(const std::vector<MazeNode*>& mazeRow){
    std::cout << Vert_wall; //Creates a vertcal wall at the left most column before each iteration
    
    //analyze nodeType for a complete row
    for (const auto& mazeNode : mazeRow) { //for each element in a mazeRow = a single mazeNode.
        switch (mazeNode->getNodeType()) {
        case NodeType::START:
            std::cout << start;
            break;
        case NodeType::END:
            std::cout << end;
            break;
        case NodeType::REGULAR:
            std::cout << RegNode;
            break;
        default:
            break;
        }
        
        //checks the context of the program and determine the behaivour of the function.
        if (this->funType == "printMatrix") {
            std::cout << Vert_wall; // print vertical wall after each node insert to surround nodes with vertical walls
        }
        else if (this->funType == "printMaze") {
            analyzeRightPtr(mazeNode); //if the context is to print the maze -> analyze the right pointers for links
        }
    }
    std::cout << "\n"; // End of the node row. This causes output to go to the beginning of next line.
}

//function that analyzes the right pointer of a specific node. depending if the pointer has a defined link or not,
// this function will print a vertical path, or a vertical wall. The input is one MazeNode
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

//Takes in a matrix row as argument and analyzes the downlink/down pointers of every node for that row to determine
//if there should be a path, or a wall at that place.
void mazeDisplayer::analyzeDownPtr(const std::vector<MazeNode*> mazeRow)
{
    std::cout << " "; // places the elements of every row one step extra to the right for symmetrical alignment 
    std::cout << "|"; //tightens the vertical gap at the leftest column 
    for (const auto& mazeNode : mazeRow) { //for each node in this row: 
        if (mazeNode->getDownPtr() != nullptr) { //if downPtr != NULL = print a path :
            std::cout << H_path << "|"; //print path & also add one extra "|" to fill the vertical gap that a horrizontal path creates
        }
        else {
            std::cout << Hori_wall; // if downPtr is not linked, print a horrizontal wall instead of path.
        }
    }
}

//Destructor of the object
mazeDisplayer::~mazeDisplayer()
{
}
