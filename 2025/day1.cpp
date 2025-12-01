#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << argv[1] << " Failed to Open" << endl;
        return -1;
    }
    
    int dial = 50;
    int p1count = 0;
    int p2count = 0;

    string line;
    char direction;
    int distance;
    int mul;
    while (getline(file, line))
    {
        direction = line[0];
        distance = stoi(line.substr(1));

        mul = direction == 'R' ? 1 : -1;

        for(int i = 0; i < distance; i++)
        {
            dial += mul;
            
            if (dial > 99) dial = 0;
            if (dial < 0) dial = 99;
            if (dial == 0) p2count++;
        }

        if (dial == 0) p1count++;
    }

    cout << "Part 1 Final Count << " << p1count << endl;
    cout << "Part 2 Final Count << " << p2count << endl;

    file.close();
    return 0;
}