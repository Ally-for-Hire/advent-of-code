#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

bool validateOpen (ifstream &file);
bool checkFront ();
bool moveForward(bool);
int currentPos ();

// Globals
string WHOLEFILE = "";
int LENGTH, X = -1, Y = -1, DIR = 1; // 1 = UP, 2 = RIGHT, 3 = DOWN, 4 = LEFT


int main()
{
    // File Validation
    ifstream dataFile("input"); 
    bool open = validateOpen(dataFile);
    if (!open) { cout << "File unable to be opened."; return 0; }

    // Variables
    string line;
    int wholeWords, row = 0, column = 0;
    char dirChar[] = {'^', '>', 'v', '<'};

    // Parse whole file into string
    while (getline(dataFile, line))
    {
        if (LENGTH == 0) { LENGTH = line.length(); }
        WHOLEFILE += line;

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
            WHOLEFILE[currentPos()] = dirChar[DIR - 1];
        }
        else
        {
            DIR = DIR % 4 + 1;
        }

        active = moveForward(false);
    }

    for (int i = 0; i < WHOLEFILE.length(); i++)
    {
        cout << WHOLEFILE[i];
        if (i % LENGTH == 0 && i > 0) { cout << endl; }
    }
    cout << endl;

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
    cout << "The answer to Part 2 is: " << endl;
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

int currentPos ()
{
    return Y * LENGTH + X;
}

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