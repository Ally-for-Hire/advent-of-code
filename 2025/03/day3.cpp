#include "../aoc.h"

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << argv[1] << " Failed to Open" << endl;
        return -1;
    }

    int part1Answer = 0;
    long long part2Answer = 0;
    string input, line;
    int firstMax, secondMax, startIndex, cur;
    while (getline(file, line)) 
    {
        firstMax = 0;
        secondMax = 0;

        for(size_t i = 0; i < line.size(); ++i)
        {
            cur = line[i] - '0';

            if (cur > firstMax && i < line.size() - 1)
            {
                firstMax = cur;
                secondMax = 0;
                continue;
            }

            if (cur > secondMax) 
                secondMax = cur;
        }

        part1Answer += (firstMax * 10 + secondMax);

        int startIndex = 0;
        int digitsLeft = 12;
        while (digitsLeft > -1)
        {
            int temp = 0;
            int newStart = 0;

            for(int i = startIndex; i < line.size() - digitsLeft + 1; ++i)
            {
                int cur = line[i] - '0';
                if(cur <= temp) continue;

                temp = cur;
                newStart = i;
            }

            part2Answer += temp * pow(10, digitsLeft - 1);
            startIndex = newStart + 1;
            digitsLeft--;
        }
    }
    
    cout << "Part 1 Answer: " << part1Answer << endl;
    cout << "Part 2 Answer: " << part2Answer << endl;

    file.close();
    return 0;
}
