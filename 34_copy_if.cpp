/* output
vector copy if 6 count:    1
init list copy if 6 count: 1
*/

#include <range/v3/algorithm/copy_if.hpp>
#include <range/v3/utility/iterator.hpp>
#include <range/v3/algorithm/for_each.hpp>
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

auto is_six = [](int i) -> bool { return i == 6; };
auto print = [] (int i) { cout << i << " "; };

int main() {

  vector<int> v { 1, 2, 3, 4, 5, 6};
  {
    // copy from one container to another
    vector<int> v_cpy;
    rng::copy_if(v, rng::back_inserter(v_cpy), is_six);
    rng::for_each( v_cpy, print ); //6    
    cout << "\n";
  }
  {
    // copy from braced init list range
    vector<int> v_cpy;
    rng::copy_if({6, 7, 8}, rng::back_inserter(v_cpy), is_six);
    rng::for_each( v_cpy, print ); //6    
    cout << "\n";
  }
}

