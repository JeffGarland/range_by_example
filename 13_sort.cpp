/* output
vector:   1 2 3 4 5 6 
array:    1 2 3 4 5 6 
deque:    6 5 4 3 2 1 
*/

#include <range/v3/algorithm/sort.hpp>   //specific includes
#include <range/v3/algorithm/for_each.hpp>  
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

  vector<int> v { 6, 2, 3, 4, 5, 1 };
  rng::sort ( v );
  rng::for_each( v, print ); //1 2 3 4 5 6

  cout << endl << "array:    ";

  array<int, 6> a { 6, 2, 3, 4, 5, 1 };
  rng::sort ( a );
  rng::for_each( a, print ); 

  //well I'm afraid you cannot sort a list...
  // list<int> li { 6, 2, 3, 4, 5, 1 };
  // auto compare = [](int i, int j) { return i < j; };
  // rng::sort ( li, compare );
  // rng::for_each( li, print );

  cout << endl << "deque:    ";
  
  deque<int> d { 6 , 2, 3, 4, 5, 1 };
  //sort in reverse 
  auto rcompare = [](int i, int j) { return i > j; };
  rng::sort ( d, rcompare );  // 6 5 4 3 2 1 
  rng::for_each( d, print ); 

  cout << endl;


}

