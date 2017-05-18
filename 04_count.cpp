// /home/jeff/devtools/gcc7/install/usr/local/bin/g++ -I /home/jeff/devtools/range_git/range-v3/include -std=c++17 04_count.cpp

/* output
vector:   2
array:    2
*/

#include <range/v3/algorithm/count.hpp>   //specific includes
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


int main() {

  cout << "vector:   ";

  vector<int> v { 6, 2, 3, 4, 5, 6 };
  int c = rng::count( v, 6 );
  
  cout << c << endl << "array:    ";

  array<int, 6> a { 6, 2, 3, 4, 5, 6 };
  c = rng::count( a, 6 );
  

  cout << c << endl;
  
  // list<int> ll { 1, 2, 3, 4, 5, 6 };
  // rng::for_each( ll, print );

  // cout << endl << "fwd_list: ";

  // forward_list<int> fl { 1, 2, 3, 4, 5, 6 };
  // rng::for_each( fl, print ); 

  // cout << endl << "deque:    ";
  
  // deque<int> d { 1, 2, 3, 4, 5, 6 };
  // rng::for_each( d, print ); 

  // cout << endl;


}

