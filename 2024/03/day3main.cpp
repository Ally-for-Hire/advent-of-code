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
    int multiplicationResult = 0;
    regex pattern("mul\\((\\d+),(\\d+)\\)"); 

    while (getline(dataFile, line))
    {
        string::const_iterator searchStart(line.cbegin());
        smatch match;

        // This is really smart and I can't take credit for it, but BAM
        while (regex_search(searchStart, line.cend(), match, pattern)) {
            multiplicationResult += stoi(match[1].str()) * stoi(match[2].str());

            searchStart = match.suffix().first; 
        }
    }
    cout << "The answer to Part 1 is: " << multiplicationResult << endl;
    
    // Part 2 Solution
    dataFile.clear();
    dataFile.seekg(0, ios::beg);
    multiplicationResult = 0;
    regex keyWordPattern("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");
    int currentlyDo = 1;

    while (getline(dataFile, line))
    {
        string::const_iterator searchStart(line.cbegin());
        smatch match;

        while (regex_search(searchStart, line.cend(), match, keyWordPattern)) {
            string value = match.str();

            if (!match.str().compare("do()"))
            {
                currentlyDo = 1;
            }
            else if (!match.str().compare("don't()"))
            {
                currentlyDo = 0;
            }
            else
            {
                multiplicationResult += stoi(match[1].str()) * stoi(match[2].str()) * currentlyDo;
            }

            searchStart = match.suffix().first; 
        }

        // test
    }
    cout << "The answer to Part 2 is: " << multiplicationResult << endl;

    dataFile.close();
    return 0;
}