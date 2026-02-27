#include "../aoc.h"

const vector<string> explode(const string&, const char&);
const int intBuilder(const char&, const char&, const char&, const char&);

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

    for(int col = 0; col < len_raw; col += 4)
    {
        char exp = input_raw[4][col];
        int num1 = intBuilder(input_raw[0][col], input_raw[1][col], input_raw[2][col], input_raw[3][col]);
        int num2 = intBuilder(input_raw[0][col+1], input_raw[1][col+1], input_raw[2][col+1], input_raw[3][col+1]);
        int num3 = intBuilder(input_raw[0][col+2], input_raw[1][col+2], input_raw[2][col+2], input_raw[3][col+2]);

        long long out;
        
        if (exp == '*')
            out = num1 * num2 * num3;
        else
            out = num1 + num2 + num3;

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

const int intBuilder(const char& a, const char& b, const char& c, const char& d)
{
    vector<int> ints;
    int num1 = a - '0';
    ints.push_back(num1 == -16 ? 0 : num1);
    int num2 = b - '0';
    ints.push_back(num2 == -16 ? 0 : num2);
    int num3 = c - '0';
    ints.push_back(num3 == -16 ? 0 : num3);
    int num4 = d - '0';
    ints.push_back(num4 == -16 ? 0 : num4);

    int output = 0;
    int tens = 0;
    for (int i = ints.size() - 1; i > -1; --i)
    {
        if (ints[i] == 0) continue;
        output += ints[i] * pow(10, tens);
        tens++;
    }

    return output;
}