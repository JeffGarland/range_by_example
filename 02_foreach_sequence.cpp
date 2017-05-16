/* output
vector:   1 2 3 4 5 6 
array:    1 2 3 4 5 6 
list:     1 2 3 4 5 6 
fwd_list: 1 2 3 4 5 6 
deque:    1 2 3 4 5 6 
*/

#include <range/v3/algorithm/for_each.hpp>   //specific includes
namespace rng = ranges::v3;

#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <array>
#include <iostream>
using namespace std;

auto print = [] (int i) { cout << i << " "; };

int main() {

  cout << "vector:   ";

  vector<int> v { 1, 2, 3, 4, 5, 6 };
  rng::for_each( v, print ); //1 2 3 4 5 6

  cout << endl << "array:    ";

  array<int, 6> a { 1, 2, 3, 4, 5, 6 };
  rng::for_each( a, print ); 

  cout << endl << "list:     ";
  
  list<int> ll { 1, 2, 3, 4, 5, 6 };
  rng::for_each( ll, print );

  cout << endl << "fwd_list: ";

  forward_list<int> fl { 1, 2, 3, 4, 5, 6 };
  rng::for_each( fl, print ); 

  cout << endl << "deque:    ";
  
  deque<int> d { 1, 2, 3, 4, 5, 6 };
  rng::for_each( d, print ); 

  cout << endl;
}

