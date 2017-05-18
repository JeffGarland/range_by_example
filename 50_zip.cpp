/* output
a : 1
b : 2
c : 3
d : 4
e : 5
*/

#include <range/v3/all.hpp>         // get everything
namespace view = ranges::v3::view;  // easy access

#include <iostream>
#include <string>
using namespace std;

int main() {

  string letters = { "abcde" };
  auto   numbers = { 1, 2, 3, 4, 5 };

  for (auto [l,n] : view::zip(letters, numbers))  // Python style zip of two ranges
    cout << l << " : " << n << endl;
}
