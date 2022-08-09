#include <cstring>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

enum Direction { NORTH = 0, WEST = 1, SOUTH = 2, EAST = 3 };

class Location {
   public:
    int x, y;
    int dir;

    Location(int i, int j) {
        x = i;
        y = j;
        // Initially direction set to -1 -- no direction tried.
        dir = -1;
    }
};

char dirToChar(int d) {
    switch (d) {
        case NORTH:
            return 'N';
        case WEST:
            return 'W';
        case SOUTH:
            return 'S';
        case EAST:
            return 'E';
        default:
            return 'X';
    }
}

// output a Location object.
ostream &operator<<(ostream &os, const Location &n) {
    os << '(' << n.x << ", " << n.y << ", " << dirToChar(n.dir) << ") ";
    return os;
}

// Output a stack object.
ostream &operator<<(ostream &os, stack<Location> my_stack) {
    // use copy parameter to copy entire stack. Needed because this
    // function destroys the stack as it prints it.
    while (!my_stack.empty()) {
        Location n = my_stack.top();
        os << n;
        my_stack.pop();
    }
    return os;
}

// Space for maze -- 100x100 is maximum.
char maze[100][100];
// Keep track of locations that have been visited.
bool visited[100][100];

// Size of the maze.
int numRows, numCols;

// Starting location
int startX, startY;
// Location of the goal.
int goalX, goalY;

/*
 * read the maze from the given file, into the maze variable.
 * the maze file starts with a line containing the number of rows and cols.
 * Maze has a character for each location:
 * S = start
 * G = goal
 * _ = hallway (empty space)
 * X = wall
 * While reading the maze, store the starting point and goal into the
 * global variables.
 * @return true if the file exists and can be read. False otherwise.
 */
bool readMazeFromFile(string fName) {
    return true;
}

bool isReachable() {
    return false;
}

// Driver code
int main() {
    string fileName;

    // Read in maze
    cout << "Enter the name of the file containing the maze: ";
    cin >> fileName;

    if (!readMazeFromFile(fileName)) {
        cerr << "Could not read given filename" << endl;
        exit(-1);
    }

    // Initially setting the visited array to false
    memset(visited, false, sizeof(visited));

    if (isReachable()) {
        cout << "Path Found!" << '\n';
    } else
        cout << "No Path Found!" << '\n';

    return 0;
}
