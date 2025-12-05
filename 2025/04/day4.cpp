#include "../aoc.h"

struct Point {
    int x = 0;
    int y = 0;
};
bool checkSurroundings(Point, Point, string&);

int main(int argc, char* argv[])
{
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << argv[1] << " Failed to Open" << endl;
        return -1;
    }

    int part1Answer = 0, part2Answer = 0;
    string input, line;
    int totalLines = 0;
    while (getline(file, line)) {
        input += line;
        totalLines++;
    }

    Point bounds;
    bounds.x = line.size();
    bounds.y = totalLines;

    for(int i = 0; i < (bounds.x * bounds.y); ++i) {
        if (input[i] == '.') continue;
        if (!checkSurroundings(Point{i % bounds.x, i / bounds.x}, bounds, input)) continue;

        part1Answer++;
    }

    part2Answer = part1Answer;
    int lastAnswer = part1Answer;
    int testAnswer = part1Answer;
    while(testAnswer != 0)
    {
        lastAnswer = testAnswer;
        testAnswer = 0;

        for(int i = 0; i < (bounds.x * bounds.y); ++i) {
            if (input[i] != 'x') continue;
            input[i] = '.';
        }

        for(int i = 0; i < (bounds.x * bounds.y); ++i) {
            if (input[i] == '.') continue;
            if (!checkSurroundings(Point{i % bounds.x, i / bounds.x}, bounds, input)) continue;

            testAnswer++;
        }

        part2Answer += testAnswer;
    }

    cout << "Part 1 Answer << " << part1Answer << endl;
    cout << "Part 2 Answer << " << part2Answer << endl;

    file.close();
    return 0;
}

bool checkSurroundings(Point point, Point bounds, string& input)
{
    vector<Point> adj;
    int count = 0;

    if (point.x > 0) adj.push_back(Point{point.x - 1, point.y}); // left
    if (point.x + 1 < bounds.x) adj.push_back(Point{point.x + 1, point.y}); // right
    if (point.y > 0) adj.push_back(Point{point.x, point.y - 1}); // top
    if (point.y + 1 < bounds.y) adj.push_back(Point{point.x, point.y + 1}); // bottom

    if (point.x > 0 && point.y > 0) adj.push_back(Point{point.x - 1, point.y - 1}); // top left
    if (point.x + 1 < bounds.x && point.y > 0) adj.push_back(Point{point.x + 1, point.y - 1}); // top right
    if (point.x > 0 && point.y + 1 < bounds.y) adj.push_back(Point{point.x - 1, point.y + 1}); // bottom left
    if (point.x + 1 < bounds.x && point.y + 1 < bounds.y) adj.push_back(Point{point.x + 1, point.y + 1}); // bottom right

    for (auto n : adj)
    {
        if (input[n.x + n.y * bounds.x] != '@' && input[n.x + n.y * bounds.x] != 'x') continue;
        
        count++;
    }

    if (count < 4) {
        input[point.x + point.y * bounds.x] = 'x';
        return true;
    }
    return false;
}