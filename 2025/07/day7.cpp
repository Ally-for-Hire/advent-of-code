#include "../aoc.h"

int journey(int, int, vector<string>&);
long long timelineJourney(int, int, vector<string>, vector<vector<long long>>&);

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) 
        return -1;

    long long part1Answer = 0, part2Answer = 0;
    string line;
    vector<string> input;
    vector<string> input_copy;
    unordered_map<string, bool> solutions;

    while (getline(file, line)) {
        input.push_back(line);
        input_copy.push_back(line);
    }
    int len = input[0].size();
    vector<vector<long long>> memo(input.size(), vector<long long>(len, -1));

    for(int i = 0; i < len; ++i)
    {
        if (input[0][i] != 'S') continue;
        
        // we start the one below S
        part1Answer = journey(i, 1, input);
        part2Answer = timelineJourney(i, 1, input_copy, memo);
        break;
    }
    
    cout << "Part 1 Answer << " << part1Answer << endl;
    cout << "Part 2 Answer << " << part2Answer << endl;

    file.close();
    return 0;
}

int journey(int x, int y, vector<string>& input)
{
    char cur = input[y][x];
    if (y + 1 == input.size()) return 0;

    int res = 0;
    if(cur == '.')
    {
        input[y][x] = '|';
        res = journey(x, y + 1, input);
    }
    else if (cur == '^')
    {   
        input[y][x+1] = '|';
        input[y][x-1] = '|';
        res = journey(x + 1, y + 1, input) + journey(x - 1, y + 1, input) + 1;
    }

    return res;
}

long long timelineJourney(int x, int y, vector<string> input, vector<vector<long long>>& memo)
{
    if (y + 1 == input.size())
        return 1;

    long long& cached = memo[y][x];
    if (cached != -1)
        return cached;

    char cur = input[y][x];

    long long res = 0;
    if(cur == '.')
        res = timelineJourney(x, y + 1, input, memo);
    else
        res = timelineJourney(x + 1, y + 1, input, memo) + timelineJourney(x - 1, y + 1, input, memo);

    cached = res;
    return res;
}