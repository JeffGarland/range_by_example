/* output
*/

// suppress warning about iota using a half-open range
#define RANGES_SUPPRESS_IOTA_WARNING

#include <range/v3/algorithm/reverse.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/algorithm/binary_search.hpp>
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

int main() {

  vector<int> v { 1, 2, 3, 3, 4, 5 };     // inputs must be sorted but may be repeated

  assert(rng::binary_search(v, 3));       // returns whether item is found
  assert(!rng::binary_search(v, 10));

  // you can supply your own comparison predicate
  rng::reverse(v);
  assert(rng::binary_search(v,   3, [](int a, int b) { return b < a; })); // reversed comparison
  assert(!rng::binary_search(v, 10, [](int a, int b) { return b < a; }));

  // and a custom "projection" function to be applied prior to the comparison
  // this one inverts the value so the range is sorted in increasing (less negative) order
  assert(rng::binary_search(v,   -3, std::less<>{}, [](int x) { return -x; }));
  assert(!rng::binary_search(v, -10, std::less<>{}, [](int x) { return -x; }));

  // "error: static assertion failed: Trying to binary search an infinite range":
  // rng::binary_search(rng::view::iota(1), 12);
  
  // finite ranges are OK
  assert(rng::binary_search(rng::view::iota(1, 6), 5));
  assert(!rng::binary_search(rng::view::iota(1, 6), 7));

}
