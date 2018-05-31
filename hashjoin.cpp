#include<iostream>
#include<vector>
#include<string>
#include<unordered_map> 
// In an unordered_multimap, a key value is used to uniquely identify the element.
// The elements in the unordered_multimap are not sorted in any particular order 
// with respect to either their key or mapped values, but organized into buckets depending on 
// their hash values to allow for fast access to individual elements directly by their key values.

using namespace std;
using tab = vector<vector<string>>;

tab hashjoin(const tab& R, uint columna, const tab& S, uint columnb) {
    unordered_multimap<string, uint> hashmap;

    // hash
    for(int i; i < R.size(); i++) {
        hashmap.insert(make_pair(S[i][comlumna], i));
    }

    // join
    tab result;
    for(int i = 0; i < S.size(); i++) {
        auto range = hashmap.equal_range(b[i][columnb]) // Retorna um par de iterators, um para o primeiro elemento do bucket e o outro para o último elemento do bucket
        for(auto it = range.first; it != range.second; ++it) {
            tab::value_type row;
            row.insert(row.end(), R[it->second].begin(), S[it->second].end());
            row.insert(row.end(), S[i].begin(), S[i].end());
            result.push_back(move(row));
        }
    }
    return result;
}

