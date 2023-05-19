#ifndef MAZEDISPLAYER_H
#define MAZEDISPLAYER_H
#include <vector>


//forward declaration of the mazeSolver class, which is a pointer/reference to the mazeSolver class.
// by using forward declaration, we can pass in a mazeSolver object that represents the solved maze into 
// the mazeDisplayer constructor.
// With forward declaration we declare the clasee mazeSolver before it's complete definition is available.
// By using forward declaration in this case, we can use the object mazeSolver as a parameter into the constructor
// without having to include the entire 'mazeSolver.h' file in this class. By doing this we reduce the chance
// or errors due to dependencies, and also reduce build/compilation time and overhead.




class mazeSolver;
class mazeGenerator;
struct MazeNode;


//template <typename T>

//class used to display the maze that has been generated and solved
// This class is listed at the highest of the maze hierachy, and can only print out the solved mazes.
class mazeDisplayer {

private:
	//mazeGenerator mazeGenerator;
	//const MazeVector& mazeVec;

	//const typename mazeGenerator::MazeVector& mazeVec;

	//const mazeGenerator::MazeVector& mazeVec;


	//mazeSolver& solvedMaze; //reference/pointer to the solved maze object.
	//mazeGenerator& maze; //reference/pointer to the generated maze datastructure
	//mazeGenerator::MazeVector& mazeVector; //vector of the maze that will be passed into this class

	char H_wall = '|';
	char V_wall = '-';
	char start = 'S'; 
	char end = 'E'; 
	char node = '*';
	char path = ' ';


	//inputs::
	//the generated maze and it's properties and data structures generated from class 'mazeGenerator'
	// the solved maze and it's data structures from the class 'mazeSolver'
	// the visual and graphical interface in how the recieved data will be represented on the screen

	//outputs
	//algorithms for displaying the generated data structures on the screen

public:

	typedef std::vector<std::vector<MazeNode*>> MazeVector;
//typedef mazeGenerator::MazeVector MazeVec;
//using MazeVector = mazeGenerator::MazeVector;



	//constructor that takes in a mazeGenerator object as input. By accessing the datastructures of the 
	//generated maze it can display the maze
	mazeDisplayer(const MazeVector& mazeVec);

	//void getMazeVec(const mazeGenerator::MazeVector mazeVec);
	//mazeDisplayer(const MazeVector& mazeVector);

	//method and logic to print the maze, this method will be called by the constructor
	// this method will access the reference object "solvedMaze" to print the maze. 
	// since this method is only responsible for printing the maze with no further
	// computations, it does not need to return a value.
	void printMaze();

};

#endif // !MAZEDISPLAYER_H

