#include "../aoc.h"

struct Range
{
    long long min = 0;
    long long max = 0;

    bool operator<(const Range& a) const
    {
        return min < a.min;
    }
    bool operator==(const Range& a) const
    {
        return min == a.min && max == a.max;
    }
};
const vector<string> explode(const string&, const char&);
const bool inRanges(const string, const vector<Range>);
const Range rangeUnion(const Range&, const Range&);

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

    bool findingRanges = true;

    vector<Range> ranges;
    
    while (getline(file, line)) 
    {
        if (line.size() == 0) { 
            findingRanges = false;
            continue;
        }

        if (findingRanges)
        {
            vector<string> test = explode(line, '-');
            Range range = Range{stoll(test[0]), stoll(test[1])};
            ranges.push_back(range);
            continue;
        }

        if (!inRanges(line, ranges))
            continue;

        part1Answer++;
    } 

    sort(ranges.begin(), ranges.end());

    for (int i = 0; i < ranges.size() - 1; ++i)
    {
        Range &cur = ranges[i];
        Range &compare = ranges[i + 1];

        if (cur.max < compare.min) 
            continue;

        compare.max = compare.max > cur.max ? compare.max : cur.max; 
        compare.min = compare.min < cur.min ? compare.min : cur.min;

        if(cur.min == compare.min)
        {
            ranges.erase(ranges.begin() + i);
            --i;
        }
    }

    for (auto n : ranges)
        part2Answer += n.max - n.min + 1;

    cout << "Part 1 Answer: " << part1Answer << endl;
    cout << "Part 2 Answer: " << part2Answer << endl;

    file.close();
    return 0;
}

const Range rangeUnion(const Range& range1, const Range& range2)
{
    Range out = Range{};
    if (range1.max < range2.min || range2.max < range1.min) return range1;
    if (range1.min > range2.min || range2.max < range1.max) return range1;
    out.min = range1.min < range2.min ? range1.min : range2.min;
    out.max = range1.max > range2.max ? range1.max : range2.max;
    return out;
}

const bool inRanges(const string num, const vector<Range> ranges)
{
    long long test = stoll(num);

    bool foundRange = false;
    for (auto n : ranges)
    {
        if (test < n.min || test > n.max)
            continue;
        
        foundRange = true;
        break;
    }

    return foundRange;
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
