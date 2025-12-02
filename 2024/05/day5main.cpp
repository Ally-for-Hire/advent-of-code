#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool validateOpen (ifstream &file);

int main()
{
    // File Validation
    ifstream ruleFile("input1"); 
    bool open = validateOpen(ruleFile);
    if (!open) { cout << "File unable to be opened."; return 0; }
    ifstream dataFile("input2"); 
    open = validateOpen(dataFile);
    if (!open) { cout << "File unable to be opened."; return 0; }

    // Global Variables
    string line, rule;

    // Part 1 Solution
    // ---------------------------------------------------------------------------//
    // plan: test every case against every rule MANUALLY
    int validRules = 0;

    while (getline(dataFile, line)) // For every line
    {
        bool followsRules = true;
        vector<int> fullLine;

        while (getline(ruleFile, rule) && followsRules) // For every rule
        {
            istringstream ruleStream (rule);
            istringstream dataStream (line);
            string beforeStr, afterStr, numberStr;
            
            getline(ruleStream, beforeStr, '|');
            getline(ruleStream, afterStr, '|');

            int before = stoi(beforeStr);
            int after = stoi(afterStr);

            int indbefore = -1, indafter = -1, index = 0;
            bool generatefullLine = fullLine.size() == 0;

            while (getline(dataStream, numberStr, ','))
            {   
                index++;

                if (generatefullLine) { fullLine.push_back(stoi(numberStr)); }

                if (stoi(numberStr) == before) { indbefore = index; }
                else if (stoi(numberStr) == after) { indafter = index; }
            }

            if (indafter < indbefore && (indbefore != -1 && indafter != -1))
            {
                followsRules = false;
            }
        }

        if (followsRules) 
        { 
            validRules += fullLine[fullLine.size() / 2]; 
        }

        ruleFile.clear();
        ruleFile.seekg(0, ios::beg);
    }

    cout << "The answer to Part 1 is: " << validRules << endl;
    // ---------------------------------------------------------------------------//
    
    dataFile.clear();
    dataFile.seekg(0, ios::beg);

    // Part 2 Solution
    // ---------------------------------------------------------------------------//
    int newlyValidRules = 0;
    
    while (getline(dataFile, line)) // For every line
    {
        bool followsRules = true;
        bool followDefault = true;
        string lineTake, lineNew;
        vector<int> fullLine;

        while (getline(ruleFile, rule)) // For every rule
        {
            if (followDefault)
            {
                lineTake = line;
            }
            else
            {
                lineTake = lineNew;
            }

            istringstream ruleStream (rule);
            istringstream dataStream (lineTake);
            string beforeStr, afterStr, numberStr;
            
            getline(ruleStream, beforeStr, '|');
            getline(ruleStream, afterStr, '|');

            int before = stoi(beforeStr);
            int after = stoi(afterStr);

            int indbefore = -1, indafter = -1, index = 0;
            bool generatefullLine = fullLine.size() == 0;

            while (getline(dataStream, numberStr, ','))
            {   
                if (generatefullLine) { fullLine.push_back(stoi(numberStr)); }

                if (stoi(numberStr) == before) { indbefore = index; }
                else if (stoi(numberStr) == after) { indafter = index; }

                index++;
            }

            if (indafter < indbefore && (indbefore != -1 && indafter != -1))
            {
                lineNew = "";
                fullLine[indbefore] = after;
                fullLine[indafter] = before;
                cout << line << " -> ";
                for (int i = 0; i < fullLine.size(); i++) 
                { 
                    lineNew += to_string(fullLine[i]) + ","; 
                }
                cout << lineNew << endl;

                followDefault = false;
                followsRules = false;

                ruleFile.clear();
                ruleFile.seekg(0, ios::beg);

                continue;
            }
        }

        if (!followsRules)
        {
            newlyValidRules += fullLine[fullLine.size() / 2]; 
        }

        ruleFile.clear();
        ruleFile.seekg(0, ios::beg);
    }

    cout << "The answer to Part 2 is: " << newlyValidRules << endl;
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