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
    int firstMax, secondMax, startIndex, cur;
    while (getline(file, line)) 
    {
        firstMax = 0;
        startIndex = 0;
        for(size_t i = 0; i + 1 < line.size(); ++i)
        {
            int cur = line[i] - '0';
            if (cur <= firstMax) continue;

            startIndex = i;
            firstMax = cur;
        }

        secondMax = 0;
        for(size_t i = startIndex + 1; i < line.size(); ++i)
        {
            cur = line[i] - '0';
            if (cur > secondMax) secondMax = cur;
        }

        part1Answer += (firstMax * 10 + secondMax);
    }
    
    cout << "Part 1 Answer: " << part1Answer << endl;
    cout << "Part 2 Answer: " << part2Answer << endl;

    file.close();
    return 0;
}
