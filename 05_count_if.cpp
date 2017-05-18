/* output
vector:   2
array:    2
*/

#include <range/v3/algorithm/count_if.hpp>   //specific includes
namespace rng = ranges::v3;

#include <vector>
#include <array>
#include <iostream>
using namespace std;

auto is_six = [](int i) -> bool { return i == 6; };

int main() {

  cout << "vector:   ";

  vector<int> v { 6, 2, 3, 4, 5, 6 };
  int c = rng::count_if( v, is_six );
  
  cout << c << endl << "array:    ";

  array<int, 6> a { 6, 2, 3, 4, 5, 6 };
  c = rng::count_if( a, is_six );
  
  cout << c << endl;
  
}

