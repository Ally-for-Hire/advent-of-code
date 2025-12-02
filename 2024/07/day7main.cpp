#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool validateOpen (ifstream &file);
vector<string> split (string, char);

int main()
{
    // File Validation
    ifstream dataFile("test"); 
    bool open = validateOpen(dataFile);
    if (!open) { cout << "File unable to be opened."; return 0; }

    // Global Variables
    string line;

    // Part 1 Solution
    // ---------------------------------------------------------------------------//
    int sum = 0;
    while (getline(dataFile, line))
    {
        istringstream lineStream (line);
        vector<string> args = split(line, ' ');
        vector<string> target = split(args[0], ':');
        
        cout << target << "  ||  ";
        for (int i = 1; i < args.size(); i++)
        {
            cout << args[i] << " ";
        }
        cout << endl;
    }
    cout << "The answer to Part 1 is: " << sum << endl;
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

vector<string> split (string input, char delimeter)
{
    istringstream inputStream (input);
    string line;
    vector<string> output;
    
    while (getline(inputStream, line, delimeter))
    {
        output.push_back(line);
    }

    return output;
}