#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const bool isValidIDSimple(const string&);
const bool isValidIDComplex(const string&);
const vector<string> explode(const string&, const char&);

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << argv[1] << " Failed to Open" << endl;
        return -1;
    }

    long long p1ans = 0, p2ans = 0;
    string input;
    getline(file, input);

    vector<string> ranges = explode(input, ',');

    for (auto n : ranges)
    {
        vector<string> range = explode(n, '-');

        long long start = stoll(range[0]);
        long long end = stoll(range[1]);

        for(long long i = start; i < end + 1; ++i)
        {
            if (!isValidIDSimple(to_string(i)))
                p1ans += i;
            if (!isValidIDComplex(to_string(i)))
                p2ans += i;
        }
    }
    
    cout << "Part 1 Answer << " << p1ans << endl;
    cout << "Part 2 Answer << " << p2ans << endl;

    file.close();
    return 0;
}

const bool isValidIDSimple(const string& s) 
{
    return s.substr(0, s.size() / 2) != s.substr(s.size() / 2);
}

const bool isValidIDComplex(const string& s)
{
    if (!isValidIDSimple(s))
        return false;

    if(s == "824824824") cout << "DING DING DING DING DING" << endl;

    for(int len = 1; len < s.size(); ++len)
    {
        if (s.size() % len != 0) 
            continue;

        string sub = s.substr(0, len);
        bool equals = true;

        for(int i = 0; i < s.size(); i += len)
        {
            string comp = s.substr(i, len);

            if (comp != sub) 
                equals = false;
        }

        if (equals)
            return false;
    }

    return true;
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