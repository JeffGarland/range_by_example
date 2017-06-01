/* output
orig vector:   { 6 2 6 4 5 6 }
unique vector: { 2 4 5 6 }
*/

#include <range/v3/algorithm/unique_copy.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/utility/iterator.hpp>
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

auto print = [] (int i) { cout << i << " "; };

int main() {

  vector<int> v { 6, 2, 6, 4, 5, 6};
  cout << "orig vector:   { ";
  rng::for_each(v, print);
  cout << "}\n";

  {
    // copy from one container to another
    vector<int> v_cpy;
    rng::sort( v ); //if you don't sort unique won't work!
    rng::unique_copy(v, rng::back_inserter(v_cpy));

    cout << "unique vector: { ";
    rng::for_each(v_cpy, print);
    cout << "}\n";
  }
}

