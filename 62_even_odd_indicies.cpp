/* output
vector: 6 2 3 4 5 6 7 8 9 1 0 
vector values at even indicies: 6 3 5 7 9 0 
vector values at odd indicies: 2 4 6 8 1 
*/

#include <range/v3/view/drop_exactly.hpp>   //specific includes
#include <range/v3/view/stride.hpp>         //specific includes
#include <range/v3/algorithm/for_each.hpp> 
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

int main() {
  auto print  = [](int i)         { cout << i << " "; };

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6, 7, 8, 9, 1, 0 };
  rng::for_each(v, print); 
  cout << endl;

  cout << "vector values at even indicies: ";
  auto evens = rng::view::stride(v, 2);
  rng::for_each(evens, print); 
  cout << endl;

  cout << "vector values at odd indicies: ";
  auto odds = rng::view::drop_exactly(v, 1) | rng::view::stride(2);
  rng::for_each(odds, print); 
  cout << endl;
}
