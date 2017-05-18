/* output
vector:   2
array:    2
*/

#include <range/v3/algorithm/count.hpp>   //specific includes
namespace rng = ranges::v3;

#include <vector>
#include <deque>
#include <iostream>
using namespace std;


int main() {

  cout << "vector:   ";

  vector<int> v { 6, 2, 3, 4, 5, 6 };
  int c = rng::count( v, 6 );
  
  cout << c << endl << "array:    ";

  array<int, 6> a { 6, 2, 3, 4, 5, 6 };
  c = rng::count( a, 6 );
  
  cout << c << endl;
  
}

