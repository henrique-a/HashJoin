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
    ifstream file("teste1.txt");
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
        auto range = hashmap.equal_range(row); // Retorna um par de ponteiros, um para o primeiro elemento do bucket com chave Sb[i] e o outro para o último elemento do bucket com chave Sb[i]
        
        for(auto it = range.first; it != range.second; ++it) { // "range.first" é o ponteiro para o primeiro elemento do bucket, "range.second" é o ponteiro para o último elemento do bucket
            output.push_back(make_pair((Ra[it->second]), atoi(row.c_str()))); // "it->second" é o valor do elemento que tá no bucket, "it->first" é a chave do bucket
        }
    }
    return output;
}

int main(int argc, char const *argv[]) {

    vector<int> col1 = readTable();
    ifstream col2("teste2.txt");

//   cout << "Column R.a: " << endl;
//   for (auto& element : col1) {
//       cout << element << endl;
//   }

//   cout << "Column S.b: " << endl;
//   for (auto& element : col2) {
//       cout << element << endl;
//   }
  
  auto result = hashjoin(col1, col2);
  cout << "Result: " << endl;

  // Imprimindo resultado
  for (auto& element : result) {
      cout << element.first << ", " << element.second << endl;
  }
  return 0;
}

