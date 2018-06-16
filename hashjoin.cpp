#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <typeinfo>
#include<unordered_map>

using namespace std;

class Hasher {
  public:
  size_t operator() (string const& key) const {
       size_t hash = 0;
        for(size_t i = 0; i < key.size(); i++) {
            hash += key[i] % 5;
        }
        cout << "Key:" << key << " --> Hash: " << hash << endl; 
        return hash;
  }
};

vector<int> readTable(){
    ifstream file("ps_partkey.txt");
    string row;
    vector<int> column;
    while (file >> row) {
        column.push_back(atoi(row.c_str()));
    }
    return column;
}
 
vector<pair<int,int>> hashjoin(const vector<int>& Ra, ifstream& Sb) {
  
    unordered_multimap<string, int, Hasher, equal_to<string>> hashmap;

    // build phase
    for(int i = 0; i < Ra.size(); i++) {
        hashmap.insert(make_pair(to_string(Ra[i]), i));
    }
    
    // probe phase
    vector<pair<int,int>> output;
    string row;
    while (Sb >> row) {
        auto range = hashmap.equal_range(row); // Returns a pair of pointers, the first points to the first element of the bucket with key Sb[i]. The second points to the last element of the bucket with key Sb[i]
        for(auto it = range.first; it != range.second; ++it) { // "range.first" is the pointer to the first element of the bucket, "range.second" is the pointer to the last element of the bucket
            output.push_back(make_pair((Ra[it->second]), atoi(row.c_str()))); // "it->second" os the value of the element in the bucket, "it->first" is the key of the bucket
        }
    }
    return output;
}

int main(int argc, char const *argv[]) {

    vector<int> col1 = readTable();
    ifstream col2("l_partsupp.txt");

    auto result = hashjoin(col1, col2);
    cout << "Result: " << endl;

    // Printing result
    for (auto& element : result) {
        cout << element.first << ", " << element.second << endl;
    }
    return 0;
}

