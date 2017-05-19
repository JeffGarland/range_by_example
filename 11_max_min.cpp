/* output
min: 1 max: 6 
min: 1 max: 6
min element 1
max element 6
min ele: 1 max ele: 6
no min element in empty vector
*/

#include <range/v3/algorithm/min.hpp> 
#include <range/v3/algorithm/max.hpp> 
#include <range/v3/algorithm/minmax.hpp>
#include <range/v3/algorithm/min_element.hpp> 
#include <range/v3/algorithm/max_element.hpp> 
#include <range/v3/algorithm/minmax_element.hpp> 

namespace rng = ranges::v3;  //easy access

#include <iostream>
#include <vector>
using namespace std;

int main() {

  vector<int> v { 1, 2, 3, 4, 5, 6 };
  {
    int min_value = rng::min( v );
    cout << "min: " << min_value << " ";
    
    int max_value = rng::max( v );
    cout << "max: " << max_value << " ";
    cout << endl;
  }
  {
    //structured bindings...c++17
    auto [min_value, max_value] = rng::minmax( v );
    cout << "min: " << min_value << " max: " << max_value << endl;
  }
  {
    //returns an iterator
    auto i = rng::min_element( v );
    if (i != v.end()) { //check it
      cout << "min element " << *i; //deref the iterator
    }
    cout << endl;
  }
  {
    auto i = rng::max_element( v );
    if (i != v.end()) { //check it
      cout << "max element " << *i;
    }
    cout << endl;
  }
  
  {
    //structured bindings...c++17...these are iterators
    auto [min_value, max_value] = rng::minmax_element( v );
    cout << "min ele: " << *min_value << " max ele: " << *max_value << endl;
  }
  {
    vector<int> v2 {};
    //i is an null iterator in this case
    //dereference causes seg fault
    auto i = rng::min_element( v2 );
    if (i == v2.end()) { //check it
      cout << "no min element in empty vector";
    }
  }
  cout << endl;

}
