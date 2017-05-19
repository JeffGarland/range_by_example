/* output
vector: 6 2 3 4 5 6 7 8 9 1 0 
vector every 3rd value: 6 4 7 1 
*/

#include <range/v3/view/stride.hpp>         //specific includes
#include <range/v3/algorithm/for_each.hpp> 
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

int main() {
  auto print  = [](int i) { cout << i << " "; };

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6, 7, 8, 9, 1, 0 };
  rng::for_each(v, print); 
  cout << endl;

  cout << "vector every 3rd value: ";
  auto strided = rng::view::stride(v, 3);
  rng::for_each(strided, print); 
  cout << endl;
}
