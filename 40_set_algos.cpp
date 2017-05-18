/* output
set s1: 1 2 3 4 5 7
set s2: 1 2 3 4 6 8
union: 1 2 3 4 5 6 7 8
intersection: 1 2 3 4
difference(s1,s2): 5 7
difference(s2,s1): 6 8
symmetric_difference: 5 6 7 8
*/

#include <range/v3/algorithm/set_algorithm.hpp>

namespace rng = ranges::v3;  //easy access

#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

void output(const vector<int>& range) {
  for (auto i : range) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {

  vector<int> s1 = {1, 2, 3, 4, 5, 7};
  cout << "set s1: ";
  output(s1);

  vector<int> s2 = {1, 2, 3, 4, 6, 8};
  cout << "set s2: ";
  output(s2);

  {
    vector<int> u;
    auto it = rng::set_union(
        s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), rng::back_inserter(u));
    cout << "union: ";
    output(u);
  }

  {
    vector<int> u;
    auto it = rng::set_intersection(
        s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), rng::back_inserter(u));
    cout << "intersection: ";
    output(u);
  }

  {
    vector<int> u;
    auto it = rng::set_difference(
        s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), rng::back_inserter(u));
    cout << "difference(s1,s2): ";
    output(u);
  }

  {
    vector<int> u;
    auto it = rng::set_difference(
        s2.cbegin(), s2.cend(), s1.cbegin(), s1.cend(), rng::back_inserter(u));
    cout << "difference(s2,s1): ";
    output(u);
  }

  {
    vector<int> u;
    auto it = rng::set_symmetric_difference(
        s2.cbegin(), s2.cend(), s1.cbegin(), s1.cend(), rng::back_inserter(u));
    cout << "symmetric_difference: ";
    output(u);
  }
}
