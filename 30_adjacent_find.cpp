#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/adjacent_find.hpp>
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;

auto print = [] (int i) { cout << i << " "; };

int main() {

  vector<int> v { 1, 2, 3, 3, 4, 5 };

  // default case: equal predicate, identity projection
  auto rpt_it = rng::adjacent_find(v);
  
  cout << "vector {";
  rng::for_each( v, print );
  cout << "} ";
  assert (rpt_it != v.end());
  cout << " has a repeated pair of entries starting at offset " << distance(v.begin(), rpt_it);
  cout << " (value " << *rpt_it << ")\n";

  // same, but not found
  vector<int> v_unique { 1, 2, 3, 4, 5, 6 };
  rpt_it = rng::adjacent_find(v_unique);
  assert( rpt_it == v_unique.end() );

  // custom predicate
  vector<int> v_skipping { 1, 2, 4, 7, 11 };
  auto gap3_it = rng::adjacent_find(v_skipping,
                                    [](int a, int b) { return b - a == 3; });
  assert( distance(v_skipping.begin(), gap3_it) == 2 );
  cout << "vector {";
  rng::for_each( v_skipping, print );
  cout << " } has a gap of 3 between entries " << distance(v_skipping.begin(), gap3_it);
  cout << " (value " << *gap3_it++ << ") and ";
  cout << distance(v_skipping.begin(), gap3_it);
  cout << " (value " << *gap3_it << ")\n";

  // predicate and projection
  vector<char> lookup{'a', 'b', 'b', 'a'};
  vector<int>  keys{0, 1, 3, 1, 2};           // indices into the lookup vector

  // find adjacent entries in keys with the same lookup char
  auto equal_lookup_it = rng::adjacent_find(keys,
                                            equal_to<>{},                              // predicate
                                            [&lookup](int x) { return lookup[x]; });   // projection
  assert( distance(keys.begin(), equal_lookup_it) == 3 );

}
