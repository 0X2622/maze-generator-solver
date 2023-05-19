#ifndef MAZEINTERFACE_H
#define MAZEINTERFACE_H
#include <vector>


class mazeGenerator;
struct MazeNode;


class mazeInterface {
public:
    //typedef std::vector<std::vector<MazeNode*>>& MazeVector;
    using MazeVector = std::vector<std::vector<MazeNode*>>;
    virtual MazeVector& getMazeVector() const = 0; //pure virtual function.
    virtual ~mazeInterface() {} 

};


#endif 

//abstract class that can be used to access specific functions from mazeGenerator (particularly the function
// get mazevector that is used to fetch the mazeVector (datastrcture). This abstract class can and will be used
// by mazeDisplayer to access the vector and print the maze. 
// by using an interface we can abstract away the logic and impolementation of the function which is handled
// by the mazegenrator class. While this class is only used to show which methods that can be used by this 
// class.

//this class is a pure virtual interface, and by having this pure virtual interface i ensure that all classes
// that derive this virtual interface must have an implementation of all virtual functions specified within it, 
// which in this case will be "getMazeVector", this class in an abstract base class 


