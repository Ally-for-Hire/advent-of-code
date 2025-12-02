#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main()
{
    ifstream dataFile("input.dat"); 

    if (!dataFile.is_open())
    {
        cout << "File not opened.";
        return 0;
    }

    vector<int> leftList;
    vector<int> rightList;
    
    int num;
    int count = 0;
    while (dataFile >> num)
    {
        count++;

        if (count % 2 == 1)
        { leftList.push_back(num); }
        else
        { rightList.push_back(num); }
    }

    sort(leftList.begin(), leftList.end());
    sort(rightList.begin(), rightList.end());

    // Part 1 Solution
    int total = 0;
    for (int i = 0; i < leftList.size(); i++)
    {
        total += abs(leftList[i] - rightList[i]);
    }
    cout << "The answer to Part 1 is: " << total << endl;
    
    // Part 2 Solution
    int similarityScore = 0;
    for (int i = 0; i < leftList.size(); i++)
    {
        int num = leftList[i];
        int count = 0;
        for (int x = 0; rightList[x] <= num; x++)
        {
            if (rightList[x] != num) { continue; }

            count++;
        }
        similarityScore += num * count;
    }
    cout << "The answer to Part 2 is: " << similarityScore << endl;

    dataFile.close();
    return 0;
}