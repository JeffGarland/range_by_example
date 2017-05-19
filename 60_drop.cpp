/* output
vector: 6 2 3 4 5 6 
vector drop half: 4 5 6 
vector drop exactly one: 2 3 4 5 6 
vector drop leading evens: 3 4 5 6 
*/

#include <range/v3/view/drop.hpp>         //specific includes
#include <range/v3/view/drop_exactly.hpp> //specific includes
#include <range/v3/view/drop_while.hpp>   //specific includes
#include <range/v3/algorithm/for_each.hpp> 
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;


int main() {
  auto print  = [](int i) { cout << i << " "; };

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6 };
  rng::for_each(v, print); 
  cout << endl;
  
  cout << "vector drop half: ";
  auto last_half = rng::view::drop(v, v.size()/2);
  rng::for_each(last_half, print); 
  cout << endl;
  
  cout << "vector drop exactly one: ";
  auto dropped_1 = rng::view::drop(v, 1);
  rng::for_each(dropped_1, print); 
  cout << endl;

  cout << "vector drop leading evens: ";
  auto is_even = [](int i) { return i % 2 == 0; };
  auto after_leading_evens = rng::view::drop_while(v, is_even);
  rng::for_each(after_leading_evens, print); 
  cout << endl;
}
