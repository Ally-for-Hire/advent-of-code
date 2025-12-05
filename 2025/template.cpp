#include "../aoc.h"

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << argv[1] << " Failed to Open" << endl;
        return -1;
    }

    int part1Answer = 0, part2Answer = 0;
    string input, line;
    while (getline(file, line)) 
        input += line;

    // Solution goes here
    
    cout << "Part 1 Answer << " << part1Answer << endl;
    cout << "Part 2 Answer << " << part2Answer << endl;

    file.close();
    return 0;
}
