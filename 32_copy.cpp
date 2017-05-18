/* output
vector: { 11 12 3 4 5 6 7 8 9 10 }
*/

#include <range/v3/view/iota.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/utility/iterator.hpp>
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

auto print = [] (int i) { cout << i << " "; };

int main() {

  vector<int> v { 1, 2, 3, 4, 5 };

  // copy from one container to another
  vector<int> v_cpy;
  rng::copy(v, rng::back_inserter(v_cpy));
  assert( v == v_cpy );
  
  // copy from braced init list range
  rng::copy({6, 7, 8}, rng::back_inserter(v_cpy));
  assert( v_cpy.size() == 8 );

  // you can copy from ranges  ("ints" gives a "half open" one, i.e. just 9 and 10):
  rng::copy(rng::view::ints(9, 11), rng::back_inserter(v_cpy));
  assert( v_cpy.size() == 10 );
  
  // you can overwrite, too
  rng::copy(rng::view::ints(11, 13), v_cpy.begin());
  assert( v_cpy.size() == 10 );

  cout << "vector: { ";
  rng::for_each(v_cpy, print);
  cout << "}\n";

}

