#include "../aoc.h"

const vector<string> explode(const string&, const char&);

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) 
        return -1;

    long long part1Answer = 0, part2Answer = 0;
    string line;
    vector<vector<string>> input;
    vector<string> input_raw;
    int expressionLine = 0;
    while (getline(file, line)) 
    {
        vector<string> exp = explode(line, ' ');
        input.push_back(exp);
        input_raw.push_back(line);
        if(exp[0] == "+" || exp[0] == "*")
            break;
        expressionLine++;
    }

    int len = input[expressionLine].size();
    int len_raw = input_raw[0].size();

    for(int col = 0; col < len; ++col)
    {
        string exp = input[expressionLine][col];
        long long out = exp == "+" ? 0 : 1;
        for(int row = 0; row < expressionLine; ++row)
        {
            long long num = stoll(input[row][col]);

            if (exp == "*") out *= num;
            else out += num;
        }
        part1Answer += out;
    }

    for(int col = 0; col < len_raw; ++col)
    {
        string expLine = input_raw[expressionLine];
        char cur = expLine[col];

        if (cur == ' ') continue;

        int w = 0, h = input.size()-1;
        while(expLine[col + ++w] == ' '); 
        w--;

        
    }

    cout << "Part 1 Answer << " << part1Answer << endl;
    cout << "Part 2 Answer << " << part2Answer << endl;

    file.close();
    return 0;
}

// Credit: https://cplusplus.com/articles/2wA0RXSz/
const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}
