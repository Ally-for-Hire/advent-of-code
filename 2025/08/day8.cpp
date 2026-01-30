#include "../aoc.h"

const vector<string> explode(const string&, const char&);
struct Point
{
    int x;
    int y;
    int z;
    vector<Point> *adj;
};

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) 
        return -1;

    int part1Answer = 0, part2Answer = 0;
    string input, line;
    vector<Point> junctions;
    vector<Point> circuits;
    while (getline(file, line)) 
    { 
        vector<string> temp = explode(line, ',');
        junctions.push_back(Point{stoi(temp[0]), stoi(temp[1]), stoi(temp[2])});
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

const int distance(Point a, Point b)
{
    return (sqrt((b.x-a.x)^2 + (b.y-a.y)^2 + (b.z-a.z)^2));
}
