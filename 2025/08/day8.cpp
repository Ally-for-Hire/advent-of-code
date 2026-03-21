#include "../aoc.h"
#include <limits>

struct Vector3
{
    int x = 0;
    int y = 0;
    int z = 0;
    int circuitIndex = -1;
};

float euclideanDistance(const Vector3&, const Vector3&);
const vector<string> explode(const string&, const char&);
void printCircuits(const vector<vector<Vector3>>&);
const pair<int, int> find2Closest(const vector<Vector3>&);
void mergeCircuits(vector<vector<int>>&, vector<Vector3>&, int a, int b);

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) 
        return -1;

    int part1Answer = 1, part2Answer = 0;
    string input, line;
    vector<Vector3> junctions;
    vector<vector<int>> circuits;

    while (getline(file, line)) 
    { 
        vector<string> temp = explode(line, ',');
        junctions.push_back(Vector3{stoi(temp[0]), stoi(temp[1]), stoi(temp[2])});
    }

    // part one, building circuits
    // do x times (currently 10)
    // find the closest 2 circuits
    // if they arent in any pre-existing circuits, make a new circuit and add them both to it
    // otherwise, add the one that isnt into the other's circuit
    // if both are in circuits, merge them into the lowest index circuit
    for (int i = 0; i < 10; i++)
    {
        auto [ia, ib] = find2Closest(junctions); // returns indices
        auto& A = junctions[ia];
        auto& B = junctions[ib];

        if (A.circuitIndex == -1 && B.circuitIndex == -1)
        {
            circuits.push_back({ia, ib});
            int idx = (int)circuits.size() - 1;
            A.circuitIndex = idx;
            B.circuitIndex = idx;
        }
        else if (A.circuitIndex == -1)
        {
            int idx = B.circuitIndex;
            circuits[idx].push_back(ia);
            A.circuitIndex = idx;
        }
        else if (B.circuitIndex == -1)
        {
            int idx = A.circuitIndex;
            circuits[idx].push_back(ib);
            B.circuitIndex = idx;
        }
        else
        {
            mergeCircuits(circuits, junctions, ia, ib);
        }
    }
    
    for (auto circuit : circuits)
        part1Answer *= circuit.size();

    cout << "Part 1 Answer: " << part1Answer << endl;
    cout << "Part 2 Answer: " << part2Answer << endl;

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

float euclideanDistance(const Vector3& a, const Vector3& b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}


void printCircuits(const vector<vector<Vector3>>& circuits)
{
    cout << "circuits: " << circuits.size() << "\n";
    for (size_t i = 0; i < circuits.size(); ++i)
    {
        cout << "  [" << i << "] size=" << circuits[i].size() << " : ";
        bool first = true;
        for (const auto& p : circuits[i])
        {
            if (!first) cout << " | ";
            first = false;
            cout << "(" << p.x << "," << p.y << "," << p.z << ")";
        }
        cout << "\n";
    }
}
