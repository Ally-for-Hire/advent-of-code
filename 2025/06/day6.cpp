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
    int expressionLine = 0, len = 0;
    while (getline(file, line)) 
    {
        vector<string> exp = explode(line, ' ');
        input.push_back(exp);
        if(exp[0] == "+" || exp[0] == "*")
            break;
        expressionLine++;
    }

    len = input[expressionLine].size();

    for(int i = 0; i < len; ++i)
    {
        string exp = input[expressionLine][i];
        long long out = exp == "+" ? 0 : 1;
        for(int g = 0; g < expressionLine; ++g)
        {
            long long num = stoll(input[g][i]);

            if (exp == "*")
                out *= num;
            else
                out += num;
        }
        part1Answer += out;
    }

    for(int i = 0; i < len; ++i)
    {
        string exp = input[expressionLine][i];
        long long out = exp == "+" ? 0 : 1;
        
        for(int g = 0; g < expressionLine; ++g)
        {
            // lines[g][i] give us the numbers to do math with
            // we need to take the numbers in each individual column
            // build final numbers out of that
            // and then do our math
            // this is weird
        }
        part2Answer += out;
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
