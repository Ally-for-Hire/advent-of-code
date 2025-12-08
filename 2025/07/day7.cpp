#include "../aoc.h"

int journey(int, int, vector<string>&);

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) 
        return -1;

    int part1Answer = 0, part2Answer = 0;
    string line;
    vector<string> input;
    while (getline(file, line)) 
        input.push_back(line);
    int len = input[0].size();

    for(int i = 0; i < len; ++i)
    {
        if (input[0][i] != 'S') continue;
        
        // we start the one below S
        part1Answer = journey(i, 1, input);
    }
    
    for(auto l : input)
        cout << l << endl;

    cout << "Part 1 Answer << " << part1Answer << endl;
    cout << "Part 2 Answer << " << part2Answer << endl;

    file.close();
    return 0;
}

int journey(int x, int y, vector<string>& input)
{
    char cur = input[y][x];
    if (y + 1 == input.size()) return 0;

    if(cur == '.')
    {
        input[y][x] = '|';

        return journey(x, y + 1, input);
    }
    else if (cur == '^')
    {
        input[y][x - 1] = '|';
        input[y][x + 1] = '|';
        
        return journey(x + 1, y + 1, input) + journey(x - 1, y + 1, input) + 1;
    }

    return 0;
}