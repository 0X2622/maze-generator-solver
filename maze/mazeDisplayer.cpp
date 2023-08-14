#include "mazeDisplayer.h"
#include "mazeGenerator.h"
#include <limits>


//ctr that initalizes the class members and also start the functions to generate the matrix and the maze
mazeDisplayer::mazeDisplayer(const std::vector<std::vector<MazeNode*>>& mazeVec) : mazeVec(mazeVec)
{
    printMatrix(); //only prints the 2D matrix datastructure
    printMaze(); //prints the generatez maze with it's path
    //setDimensions();
    //NodesLinker();
    FindNodeType();
    DFS_MazeSolver();
}


//prints the 2D matrix structure with all nodes & walls. Purpose to give the user a clear representation
// of the complete 2D matrix with start and end points.
void mazeDisplayer::printMatrix()
{
    this->context = "printMatrix"; //value to determine behaviour of "printRowNode"
    this->printHorisontalWall(); //print a long horrizontal wall along the top of the matrix to create a "roof"

    //for each element in mazeVec, where each element = a complete row, 6 in total. 
    //For all individual rows, print their respective nodes and walls
    for (const auto& mazeRow : mazeVec) {
        printNodeRow(mazeRow); //each iteration is equal to one complete row of printed nodes
        printHorisontalWall(); //after each row of printed nodes a horrizontal wall is placed beneath the row sfor sepparation.
    }

    //indicates that the visual datastrucuture has been made so that the method "printnodesrow" won't 
    // push back new rows next time it's called
    //matrixGenerated_FLAG = 1; 

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
    this->context = "printMaze"; //sets the context/state of the program.
    this->printHorisontalWall(); //print a long horrizontal wall at the top of the matrix to create a "roof"

    // For each maze row, print the respective nodes, analyze their pointers and print wall/or path, do it for all rows.
    for (const auto& mazeRow : mazeVec) {
        printNodeRow(mazeRow); //prints out nodes for a row and analyzes its right pointers
        analyzeDownPtr(mazeRow); //analyzes the whole same row again for its down pointers for horizontal walls/paths
        std::cout << "\n"; // Move output cursor down to next line for processing the next row.
    }

    std::cout << "Press any key + enter to solve the generated maze";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    //std::cout << "\033[2J\033[1;1H";
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

    // Creates a temporary row vector that will store the visual representation of nodes for a complete row
    // which then will be pushed back into visual mazeVec - which will be used to 
    // solve and print the visual maze
    //std::vector<VisualNode*> row; 
    //std::pair<int, int>Coordinates; //temporary variable "coordinates" that will hold coordinates to a node
    std::vector<std::string> row;
    std::cout << Vert_wall; //Creates a vertcal wall at the left most column before each iteration
    
    //analyze nodeType for a complete row
    for (const auto& mazeNode : mazeRow) { //for each element in a mazeRow = a single mazeNode.
        switch (mazeNode->getNodeType()) {
        case NodeType::START: {
            std::cout << start;
            //LastDirection = "RIGHT";
            //BackTrack();
            std::cout << "\033[s"; //saves the cursor position for maze path solving from the start point.
            //Coordinates = std::make_pair(mazeNode->getCoordinatesFirst(), mazeNode->getCoordinatesSecond());
            
            //instansiataing a new object "VisualNode", that will hold the same characteristics as the node
            // from the mazeVector, the purpose is so that this visual node will have the same coordinates
            // in the visual matrix as the MazeNodes coordinates in the mazeVec, and thus they are perfectly
            // syncronized in terms of the structure. The node also gets marked as "S" which indicates that
            // its a start node, and then we create a pointer sNode (start node) that points towards the 
            // address of the new visual node, and this node then gets pushed back into "visualMazeVec"
            //VisualNode* sNode = new VisualNode(Coordinates, " S "); //sNode stands for start Node
            //sNode->SetNodeType("start"); //sets the visual representation of the node in the matrix
            //std::cout << sNode->GetNodeType(); //prints out the node
            //row.push_back(sNode); //pushes the start node into the nodesvector
            row.push_back(start);
            break; }
        case NodeType::END: {
            std::cout << end;
            //Coordinates = std::make_pair(mazeNode->getCoordinatesFirst(), mazeNode->getCoordinatesSecond());
            //VisualNode* eNode = new VisualNode(Coordinates, " E "); //sNode stands for start Node
            //eNode->SetNodeType("end");
            //std::cout << eNode->GetNodeType();
            //row.push_back(eNode);
            row.push_back(end);
            break; }
        case NodeType::REGULAR: {
            //std::cout << RegNode;
            //Coordinates = std::make_pair(mazeNode->getCoordinatesFirst(), mazeNode->getCoordinatesSecond());
            //VisualNode* rNode = new VisualNode(Coordinates, " * "); //sNode stands for start Node
            //rNode->SetNodeType("reg");
            if (context == "printMatrix") {
                std::cout << RegNode;
            }
            else if (context == "printMaze") {
                std::cout << "   ";
            }
            row.push_back(RegNode);
            break; }
        default:
            break;
        }
        
        //checks the context of the program and determine the behaivour of the function.
        if (this->context == "printMatrix") {
            std::cout << Vert_wall; // print vertical wall after each node insert to surround nodes with vertical walls
        }
        else if (this->context == "printMaze") {
            analyzeRightPtr(mazeNode); //if the context is to print the maze -> analyze the right pointers for links
        }
    }


    //what im doing to to create a vector that will hold pointers to the visual node objects.
    // by having a container of the visual datastructure of the nodes, we can access it for solving the
    // maze by checking which visual nodes that have a path between or not.
    //if (matrixGenerated_FLAG == 0) {
      //  VisualMazeVec.push_back(row); //pushes back the entire row (vector) of visual nodes into the vector
    //}

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

//iterates through all nodes in the mazeVec, and check their linkings, and at the same time iterates
//through the nodes in the VisualNodesVec, and make sure to mirror the linking in mazeVec, to make sure
//that these two datastructures have the same mirrored linkings and mazepath.
/*void mazeDisplayer::NodesLinker()
{

    for (auto& MazeRow : mazeVec) {
        for (auto& mazeNode : MazeRow) {

            //makes sure that the coordinates of the visual node corresponds to the nodes of the mazeNode
            int i = mazeNode->getCoordinatesFirst(); 
            int j = mazeNode->getCoordinatesSecond();
            //VisualNode* visualNode = VisualMazeVec[i][j];

            //maybe add potential check to check boundaries to make an extra safe filter.
            if (j > 0) {
                if (mazeNode->getLeftPtr() != nullptr) { // != nullptr means that the pointer is linked to a node
                    //visualNode->setLeftPtr(VisualMazeVec[i][j - 1]); //links left node to the right
                    VisualMazeVec[i][j]->setLeftPtr(VisualMazeVec[i][j - 1]);
                    VisualMazeVec[i][j - 1]->setRightPtr(VisualMazeVec[i][j]);
                }
            }
            if (i > 0) {
                if (mazeNode->getUpPtr() != nullptr) {
                    VisualMazeVec[i][j]->setUpPtr(VisualMazeVec[i - 1][j]);
                    VisualMazeVec[i - 1][j]->setDownPtr(VisualMazeVec[i][j]);
                }
            }
            if (j+1 <= mazeWidth - 1 ) {
                if (mazeNode->getRightPtr() != nullptr) {
                    VisualMazeVec[i][j]->setRightPtr(VisualMazeVec[i][j + 1]);
                    VisualMazeVec[i][j + 1]->setLeftPtr(VisualMazeVec[i][j]);
                }
            }
            if (i+1 < mazeHeight-1) {
                if (mazeNode->getDownPtr() != nullptr) {
                    VisualMazeVec[i][j]->setDownPtr(VisualMazeVec[i + 1][j]);
                    VisualMazeVec[i + 1][j]->setUpPtr(VisualMazeVec[i][j]);
                }
            }
        }
    }
}*/

void mazeDisplayer::FindNodeType()
{
    for (auto& mazeRow : mazeVec) {
        for (auto& mazeNode : mazeRow) {
            switch (mazeNode->getNodeType()) {
                case NodeType::START: {
                    this->StartNode = mazeNode;
                    break;
                }
                case NodeType::END: {
                    this->EndNode = mazeNode;
                    break;
                }
            }
        }
        if (StartNode != nullptr && EndNode != nullptr) { //if both nodes are found breaks out of outer loop
            break;
        }
    }
}

//sets the visited flag of all nodes to false for the MazeSolver to work properly.
void mazeDisplayer::AdjustVisited()
{
    for (auto& MazeRow : mazeVec) {
        for (auto& MazeNode : MazeRow) {
            MazeNode->setVisited(false);
        }
    }
}

void mazeDisplayer::AdjustStartPos()
{
    std::cout << "\033[D" << "\033[D" << "\033[D";
    if (mazeVec.size() >= 23 && mazeVec[0].size() >= 23) {
        std::cout << "\033[B" << "\033[B";
    }
    else if (mazeVec.size() >= 24 && mazeVec[0].size() >= 24) {
        //std::cout << "\033[A" << "\033[A" << "\033[A" << "\033[A" << "\033[A" << "\033[A" << "\033[A" << "\033[A";
        StepUp();
        //return;
    }
}

//recursive DFS function that solves the maze and creates a visual path while solving it
void mazeDisplayer::DFS_MazeSolver()
{
    context = "Solving";
    //makes sure that the StartNode is only pushed once into the nodestack
    if (this->GenerateFlag == 0) {
        AdjustVisited(); //sets all nodes.visited = false, for the mazesolving algorithm.
        std::cout << "\033[u"; // Restore cursor position to the marked startnode
        AdjustStartPos();
        this->Tracker = StartNode; //startnode will at this point point towards the start of the path
        this->NodeStack.push(StartNode);
        this->GenerateFlag = 1;
    }

    if (Tracker == EndNode) { //can också be if(NodeStack.empty())
        std::cout << "Maze solving is complete!" << std::endl;
        std::cout << "Press any key + enter to return to the main menu";
        
        //these 3 following lines i can make a function of
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        std::cout << "\033[2J\033[1;1H"; // Clear screen
        
        return; // Exit the function -> needed ? 
    }
    else if (!NodeStack.empty()) {

        this->Tracker = NodeStack.top();
        Tracker->setVisited(true); //sets the currently pointed node as visited

        //important to also check if visited == false, so that the algorithm won't visit an already visited
        //node that has links again.
        if (Tracker->getLeftPtr() != nullptr && Tracker->getLeftPtr()->getVisited() == false) {
            std::cout << MazePathLeft;
            //Tracker->setVisited(true); //sets the currently pointed node as visited
            StepLeft(); //moves the cursor towards the step direction.
            NodeStack.push(Tracker->getLeftPtr()); //pushes the node left of the tracker to the stack
            // Sleep for a short duration to see the real-time effect (optional)
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        else if (Tracker->getUpPtr() != nullptr && Tracker->getUpPtr()->getVisited() == false) {
            std::cout << MazePathUp;
            //Tracker->setVisited(true);
            StepUp();
            NodeStack.push(Tracker->getUpPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        else if (Tracker->getRightPtr() != nullptr && Tracker->getRightPtr()->getVisited() == false) {
            std::cout << MazePathRight;
            //Tracker->setVisited(true);
            StepRight();
            NodeStack.push(Tracker->getRightPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        else if (Tracker->getDownPtr() != nullptr && Tracker->getDownPtr()->getVisited() == false) {
            std::cout << MazePathDown;
            //Tracker->setVisited(true);
            StepDown();
            NodeStack.push(Tracker->getDownPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        else {
            //backtrack cursor function here in the case of no linked nodes
            //change direction of stepping path
            context = "BackTracking";
            BackTrack();
            NodeStack.pop();
        } 
    }
    //if no linked nodes found -> Backtrack and pop
    DFS_MazeSolver(); //recursively calls itself
}

void mazeDisplayer::StepUp()
{
    std::cout << "\033[A" << "\033[A" << "\033[D" << "\033[D" << "\033[D"; //move cursor up one level
    StepDirection = "UP";
    if (context == "BackTracking"){ //if called from the backtracker then it should be going the same way as the function
        BackTrackDirection = "UP";
    }
    else { BackTrackDirection = "DOWN"; }
}
void mazeDisplayer::StepDown()
{
    std::cout << "\033[B" << "\033[B" << "\033[D" << "\033[D" << "\033[D";
    StepDirection = "DOWN";
    if (context == "BackTracking") {
        BackTrackDirection = "DOWN";
    }
    else { BackTrackDirection = "UP"; }
}
void mazeDisplayer::StepLeft()
{
    std::cout << "\033[D" << "\033[D" << "\033[D" << "\033[D" << "\033[D" 
        << "\033[D" << "\033[D" << "\033[D" << "\033[D";
    StepDirection = "LEFT";
    if (context == "BackTracking") {
        BackTrackDirection = "LEFT";
    }
    else { BackTrackDirection = "RIGHT"; }
}
void mazeDisplayer::StepRight()
{
    std::cout << "   ";
    StepDirection = "RIGHT";
    if (context == "BackTracking") {
        BackTrackDirection = "RIGHT";
    }
    else { BackTrackDirection = "LEFT"; }
}
void mazeDisplayer::BackTrack()
{
    if (BackTrackDirection == "UP") {
        std::cout << MazePathUp;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        StepUp();
    }
    else if (BackTrackDirection == "DOWN") {
        std::cout << MazePathDown;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        StepDown();
    }
    else if (BackTrackDirection == "LEFT") {
        std::cout << MazePathLeft;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        StepLeft();
    }
    else if (BackTrackDirection == "RIGHT") {
        std::cout << MazePathRight;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        StepRight();
    }
}

//Destructor of the object
mazeDisplayer::~mazeDisplayer()
{
    /*
    for (auto& mazeRow : this->VisualMazeVec) { //fetches vectors that hold entire mazeRows.
        for (auto& node : mazeRow) { //iterates through all nodes in the entire fetched fector
            delete node; // Deallocates the memory for the node
        }
        mazeRow.clear(); // Clear the vector for this row once all nodes are deleted (maybe i can delete this shit?)
    }
    this->VisualMazeVec.clear(); // Clear the outer vector*/
}

