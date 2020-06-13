#include "bits/stdc++.h"

using namespace std;

int main()
{
    int count_v = 10000; //顶点数
    int count_e = 40000; //边数

    for (count_e = 20000; count_e <= 280000; count_e += 20000)
    for (count_v = count_e/10; count_v <= count_e/5; count_v += count_e/40) {
        map<int, unordered_set<int>> mp;
        unordered_set<int> st_temp;
        for (int i = 0; i < count_v; i++)
            mp.insert(pair<int, unordered_set<int>>(i, st_temp));

        for (int i = 0; i < count_e; i++)
        {
            int from = rand() % count_v;
            int to = rand() % count_v;
            while (from == to || mp[from].find(to) != mp[from].end())
            {
                from = rand() % count_v;
                to = rand() % count_v;
            }
            mp[from].insert(to);
        }
        string filename = "test_data_e"+to_string(count_e)+"v"+to_string(count_v)+".txt";
        ofstream outfile(filename);
        // ofstream outfile("test_data_test.txt");
        for (auto iter = mp.begin(); iter != mp.end(); ++iter)
        {
            for (auto iter1 = iter->second.begin(); iter1 != iter->second.end(); ++iter1)
            {
                outfile << iter->first << "," << *iter1 << ",100" << endl;
            }
        }
    }
}