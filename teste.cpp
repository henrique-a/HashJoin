#include<vector>
#include<string>
#include<unordered_map>
#include "hashfunc.h"

using namespace std;

class Hasher {
    public:
  size_t operator() (string const& key) const {
      const char * key_c = key.c_str();
      const unsigned char* u_key_c = reinterpret_cast<const unsigned char *>(key_c);
      size_t hash = hash_any(u_key_c, sizeof(u_key_c));
      return hash;
  }
};

vector<int> col1 = {1,2,3,45,23,67,4,5,6};
 
vector<int> col2 = {2,4,10,11,3,15,67};

vector<pair<int,int>> hashjoin(const vector<int>& Ra, const vector<int>& Sb) {
  
    unordered_multimap<int, int> hashmap;

    // build phase
    for(int i = 0; i < Ra.size(); i++) {
        hashmap.insert(make_pair(Ra[i], i));
    }
    
    // probe phase
    vector<pair<int,int>> output;
    for(int i = 0; i < Sb.size(); i++) {
        auto range = hashmap.equal_range(Sb[i]); // GET THE ERROR HERE
        
        for(auto it = range.first; it != range.second; ++it) {
            output.push_back(make_pair(Ra[it->second], Sb[i]));
        }
    }
    return output;
}

int main(int argc, char const *argv[]) {

  cout << "Column R.a: " << endl;
  for (auto& element : col1) {
      cout << element << endl;
  }

  cout << "Column S.b: " << endl;
  for (auto& element : col2) {
      cout << element << endl;
  }
  
  auto result = hashjoin(col1, col2);
  cout << "Result: " << endl;
  for (auto& element : result) {
      cout << element.first << ", " << element.second << endl;
  }
  return 0;
}

