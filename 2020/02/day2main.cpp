#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
using namespace std;

int main()
{
    ifstream dataFile("input.dat"); 

    if (!dataFile.is_open())
    {
        cout << "File not opened.";
        return 0;
    }

    // Part 1 Solution
    string line;
    int validPasswords = 0;
    while (getline(dataFile, line))
    {
        istringstream lineStream (line);
        int min, max;
        string key;

        lineStream >> min; lineStream >> max;
        max = abs(max);
        lineStream >> key;
        key = key[0];
        
        int lengthPrior = line.length();
        regex r(key);
        string result = regex_replace(line, r, "");

        int difference = (lengthPrior - result.length() - 1);

        validPasswords += (difference >= min && difference <= max);
    }
    cout << "The answer to Part 1 is: " << validPasswords;
    
    // Part 2 Solution
    

    dataFile.close();
    return 0;
}