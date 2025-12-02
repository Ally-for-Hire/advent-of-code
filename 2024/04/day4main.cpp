#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool validateOpen (ifstream &file);
bool validateDir (string, int, int, char*, int, int); 
int booltoint (bool); 

int main()
{
    // File Validation
    ifstream dataFile("input"); 
    bool open = validateOpen(dataFile);
    if (!open) { cout << "File unable to be opened."; return 0; }

    // Global Variables
    string line, wholefile;
    int length, wholeWords = 0;

    while (getline(dataFile, line))
    {
        if (length == 0) { length = line.length(); }
        wholefile += line;
    }

    // Part 1 Solution
    // ---------------------------------------------------------------------------//
    char nextletters[] = {'M', 'A', 'S'};

    for (int i = 0; i < wholefile.length(); i++)
    {
        char letter = wholefile[i];
        if (letter != 'X') { continue; }

        for (int direction = 0; direction <= 7; direction++)
        {
            bool check = validateDir(wholefile, length, i, nextletters, 3, direction);
            wholeWords += booltoint(check);
        }
    }
    cout << "The answer to Part 1 is: " << wholeWords << endl;
    // ---------------------------------------------------------------------------//
    
    dataFile.clear();
    dataFile.seekg(0, ios::beg);
    wholeWords = 0;

    // Part 2 Solution
    // ---------------------------------------------------------------------------//
    char mArray[] = {'M'};
    char sArray[] = {'S'};

    for (int i = 0; i < wholefile.length(); i++)
    {
        char letter = wholefile[i];
        if (letter != 'A') { continue; }

        // Up, Down, Left, Up Left, Down Left, Right, Up Right, Down Right
        int checkULDR1 = validateDir(wholefile, length, i, mArray, 1, 3) + validateDir(wholefile, length, i, sArray, 1, 7) == 2;
        int checkULDR2 = validateDir(wholefile, length, i, sArray, 1, 3) + validateDir(wholefile, length, i, mArray, 1, 7) == 2;

        int checkDLUR1 = validateDir(wholefile, length, i, mArray, 1, 4) + validateDir(wholefile, length, i, sArray, 1, 6) == 2;
        int checkDLUR2 = validateDir(wholefile, length, i, sArray, 1, 4) + validateDir(wholefile, length, i, mArray, 1, 6) == 2;

        wholeWords += booltoint((checkULDR1 || checkULDR2) && (checkDLUR1 || checkDLUR2));
    }
    
    cout << "The answer to Part 2 is: " << wholeWords << endl;
    // ---------------------------------------------------------------------------//

    dataFile.close();
    return 0;
}

int booltoint (bool value) { return value && 1 || 0; }

bool validateOpen (ifstream &file)
{
    if (!file.is_open())
    {
        return false;
    }
    return true;
}

bool checkIndex (string wholefile, int index, char search)
{
    if (wholefile[index] == search)
    {
        return true;
    }    
    return false;
}

bool validateDir (string wholefile, int length, int index, char nextletters[], int arrayLength, int direction)
{
    int localIndex = index;
    int currentRow = index / length;

    for (int x = 0; x < arrayLength; x++)
    {
        // Up, Down, Left, Up Left, Down Left, Right, Up Right, Down Right
        if (direction == 0) { localIndex -= length; currentRow -= 1;}
        else if (direction == 1) { localIndex += length; currentRow += 1;}
        else if (direction == 2) { localIndex -= 1; }
        else if (direction == 3) { localIndex -= length; localIndex -= 1; currentRow -= 1; }
        else if (direction == 4) { localIndex += length; localIndex -= 1; currentRow += 1; }
        else if (direction == 5) { localIndex += 1; }
        else if (direction == 6) { localIndex -= length; localIndex += 1; currentRow -= 1; }
        else if (direction == 7) { localIndex += length; localIndex += 1; currentRow += 1; }
        else { return false; }

        if (localIndex < 0 || localIndex > wholefile.length() - 1) { return false; }
        if (localIndex / length != currentRow) { return false; }
        
        if (!checkIndex(wholefile, localIndex, nextletters[x])) { return false; }
    }

    return true;
}
