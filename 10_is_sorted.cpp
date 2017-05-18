/* output
vector:   true
array:    false
*/

#include <range/v3/algorithm/is_sorted.hpp>   //specific includes
namespace rng = ranges::v3;

#include <vector>
#include <array>
#include <iostream>
using namespace std;

int main() {

  cout << "vector:   ";

  vector<int> v { 1, 2, 3, 4, 5, 6 };
  if (rng::is_sorted( v )) { cout << "true" << endl; };
  
  cout << "array:    ";

  array<int, 6> a { 6, 2, 3, 4, 5, 6 };
  if (!rng::is_sorted( a )) { cout << "false" << endl; };
  
}

