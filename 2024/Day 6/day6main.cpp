#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

bool validateOpen (ifstream &file);
bool checkFront ();
bool moveForward(bool);
int currentPos ();
bool runSim();

// Globals
string WHOLEFILE = "";
string WHOLEFILECOPY = "";
int LENGTH, X = -1, Y = -1, DIR = 1; // 1 = UP, 2 = RIGHT, 3 = DOWN, 4 = LEFT
int STARTX, STARTY;
char DIRCHAR[] = {'^', '>', 'v', '<'};

int main()
{
    // File Validation
    ifstream dataFile("test"); 
    bool open = validateOpen(dataFile);
    if (!open) { cout << "File unable to be opened."; return 0; }

    // Variables
    string line;
    int wholeWords, row = 0, column = 0;

    // Parse whole file into string
    while (getline(dataFile, line))
    {
        if (LENGTH == 0) { LENGTH = line.length(); }
        WHOLEFILE += line;
        WHOLEFILECOPY += line;

        // Search for starting position
        if (X != -1) { continue; }

        istringstream lineStream (line);
        column = 0;
        char curChar;

        while (lineStream >> curChar) 
        {
            if ( curChar == '^' )
            {
                X = column;
                Y = row;
            }

            column += 1;
        }

        row += 1;
    }
    
    STARTX = X;
    STARTY = Y;

    cout << "Starting Position: [" << X << ", " << Y << "]" << endl;

    // Part 1 Solution
    // ---------------------------------------------------------------------------//
    bool active = true;
    int points = 1;
    while (active)
    {
        //WHOLEFILE[currentPos()] == '.';
        if (checkFront())
        {
            WHOLEFILE[currentPos()] = 'X';
            moveForward(true);
            //WHOLEFILE[currentPos()] = DIRCHAR[DIR - 1];
        }
        else
        {
            DIR = DIR % 4 + 1;
        }

        active = moveForward(false);
    }

    for (int i = 0; i < WHOLEFILE.size(); i++)
    {
        if (WHOLEFILE[i] == 'X') 
        {
            points++;
        }
    }
    cout << "The answer to Part 1 is: " << points << endl;
    // ---------------------------------------------------------------------------//
    
    dataFile.clear();
    dataFile.seekg(0, ios::beg);

    // Part 2 Solution
    // ---------------------------------------------------------------------------//
    int noExits = 0;

    for (int i = 0; i < WHOLEFILECOPY.length(); i++)
    {
        if (WHOLEFILECOPY[i] != '.' || WHOLEFILECOPY[i] == 'X') { continue; }

        WHOLEFILECOPY[i] = '%';

        if (runSim() == false)
        {
            noExits += 1;
        }
        WHOLEFILECOPY[i] = '.';
    }
    cout << "The answer to Part 2 is: " << noExits << endl;
    // ---------------------------------------------------------------------------//
    dataFile.close();
    return 0;
}

bool validateOpen (ifstream &file)
{
    if (!file.is_open())
    {
        return false;
    }
    return true;
}

int currentPos () { return Y * LENGTH + X; }
int currentPos (int length, int x, int y) { return y * length + x; }

bool checkFront ()
{
    char front;
    // Up Right Down Left
    if (DIR == 1) { front = WHOLEFILE[currentPos() - LENGTH]; }
    else if (DIR == 2) { front = WHOLEFILE[currentPos() + 1]; }
    else if (DIR == 3) { front = WHOLEFILE[currentPos() + LENGTH]; }
    else if (DIR == 4) { front = WHOLEFILE[currentPos() - 1]; }

    return front == '.' || front == 'X';
}
bool checkFront (string wholefile, int length, int dir)
{
    char front;
    // Up Right Down Left
    if (dir == 1) { front = wholefile[currentPos() - length]; }
    else if (dir == 2) { front = wholefile[currentPos() + 1]; }
    else if (dir == 3) { front = wholefile[currentPos() + length]; }
    else if (dir == 4) { front = wholefile[currentPos() - 1]; }

    return front == '.' || front == 'X';
}

bool moveForward (bool doMove)
{
    char front;

    int localIndex = currentPos();
    int currentRow = currentPos() / LENGTH;

    // Up Right Down Left
    if (DIR == 1) { localIndex -= LENGTH; currentRow -= 1; }
    else if (DIR == 2) { localIndex += 1; }
    else if (DIR == 3) { localIndex += LENGTH; currentRow += 1; }
    else if (DIR == 4) { localIndex -= 1; }

    if (localIndex < 0 || localIndex > WHOLEFILE.length() - 1) { return false; }
    if (localIndex / LENGTH != currentRow) { return false; }

    if (doMove)
    {
        X = localIndex % LENGTH;
        Y = localIndex / LENGTH;
    }

    return true;
}

bool moveForward (string wholefile, int length, int &xptr, int &yptr, int dir, bool doMove)
{
    char front;

    int localIndex = currentPos(length, xptr, yptr);
    int currentRow = currentPos(length, xptr, yptr) / length;

    // Up Right Down Left
    if (dir == 1) { localIndex -= length; currentRow -= 1; }
    else if (dir == 2) { localIndex += 1; }
    else if (dir == 3) { localIndex += length; currentRow += 1; }
    else if (dir == 4) { localIndex -= 1; }

    if (localIndex < 0 || localIndex > wholefile.length() - 1) { return false; }
    if (localIndex / length != currentRow) { return false; }

    if (doMove)
    {
        xptr = localIndex % length;
        yptr = localIndex / length;
    }

    return true;
}

bool runSim()
{
    bool active = true;

    string localWHOLEFILE = WHOLEFILECOPY;
    int localLENGTH = LENGTH;
    int localX = STARTX;
    int localY = STARTY;
    int localDIR = DIR;

    int iterations = 0;

    while (active)
    {
        if (checkFront(localWHOLEFILE, localLENGTH, localDIR))
        {
            localWHOLEFILE[currentPos(localLENGTH, localX, localY)] = 'X';
            moveForward(localWHOLEFILE, localLENGTH, localX, localY, localDIR, true);
        }
        else
        {
            localDIR = localDIR % 4 + 1;
        }

        active = moveForward(localWHOLEFILE, localLENGTH, localX, localY, localDIR, false);

        if (iterations > 10000)
        {
            cout << "No solution found after 1000 iterations." << endl;
            return false;
        }

        iterations++;
    }
    
    
    cout << "Current test: " << endl << "    ";
    for (int i = 0; i < localWHOLEFILE.length(); i++)
    {
        cout << localWHOLEFILE[i];
        if (i % LENGTH == 0 && i > 0) { cout << endl << "    "; }
    }
    cout << endl;
    

    return true;
}