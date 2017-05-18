/* output
set:           1 2 3 4 5 6 
map:           one:1 three:3 two:2 
unordered_map: three:3 one:1 two:2 
unordered_set: 6 5 4 3 2 1 
*/

#include <range/v3/algorithm/for_each.hpp>   //specific includes
namespace rng = ranges::v3;

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
using namespace std;

auto print =  [] (int i) { cout << i << " "; };
//must take a pair for map types
auto printm = [] (pair<string, int> p) { cout << p.first << ":" << p.second << " "; };

int main() {
  
  cout << "set:           ";

  set<int> si { 1, 2, 3, 4, 5, 6 };
  rng::for_each( si, print );

  cout << endl << "map:           ";

  map<string, int> msi { { "one", 1 }, { "two", 2 }, { "three", 3 } };
  rng::for_each( msi, printm );

  cout << endl << "unordered_map: ";

  unordered_map<string, int> umsi { { "one", 1 }, { "two", 2 }, { "three", 3 } };
  rng::for_each( umsi, printm );

  cout << endl << "unordered_set: ";

  unordered_set<int> usi { 1, 2, 3, 4, 5, 6 };
  rng::for_each( usi, print );

  cout << endl;

}
