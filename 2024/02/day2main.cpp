#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

bool checkSafe (istringstream& stream, int ignore);

int main()
{
    // Beginning Init
    ifstream dataFile("input.dat"); 

    if (!dataFile.is_open())
    {
        cout << "File not opened.";
        return 0;
    }

    // Part 1 Solution
    string line;
    int safeLines = 0;
    bool isSafe;

    while (getline(dataFile, line))
    {
        istringstream stream(line);
        isSafe = checkSafe(stream, -1);

        if (isSafe) 
        { 
            safeLines++; 
        }
    }

    cout << "The solution to Part 1 is: " << safeLines << endl;

    // Part 2 Solution
    dataFile.clear();
    dataFile.seekg(0, ios::beg);
    int safeDampenedLines = 0;

    while (getline(dataFile, line))
    {
        istringstream stream(line);
        isSafe = checkSafe(stream, -1);

        if (isSafe == true)
        {
            safeDampenedLines++;
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                istringstream testStream(line);
                bool testSafe = checkSafe(testStream, i);  
                if (testSafe == true)
                {
                    //cout << line << " FIXED AT INDEX " << i << endl;
                    safeDampenedLines++;
                    break;
                }
            }  
        }
    }

    cout << "The solution to Part 2 is: " << safeDampenedLines << endl;

    // Closing
    dataFile.close();
    return 0;
}

bool checkSafe(istringstream& stream, int ignore)
{
    int num, lastNum, data = 0;
    int index = 1;
    bool isSafe = true;
    bool attemptedFix = false;
    if (ignore == 0)
    {
        stream >> lastNum;
    }
    stream >> lastNum;

    while (stream >> num)
    {
        if (index == ignore) { index++; continue; }

        int difference = (lastNum - num);
        int normalized = clamp(difference, -1, 1);
        index++;

        if (abs(difference) > 3 || abs(difference) < 1) 
        { 
            isSafe = false; 
            break; 
        }

        if (data == 0) 
        { 
            data = normalized; 
        }
        else
        {
            isSafe = (normalized == data);
            if (isSafe == false) { break; }
        }

        lastNum = num;
    }

    return isSafe;
}
