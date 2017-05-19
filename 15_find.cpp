/* output
vector:   *i: 6
didn't find 10
*i: 6
*i: 2
*i after ++ (2 expected): 2
array:    *i: 6
list:     *i: 6
fwd_list: *i: 4
deque:    *i: 6
*/

#include <range/v3/all.hpp>
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
auto is_six = [](int i) -> bool { return i == 6; };

int main() {

  cout << "vector:   ";

  vector<int> v { 6, 2, 6, 4, 6, 1 };
  {
    auto i = rng::find( v, 6 ); //1 2 3 4 5 6
    cout << "*i: " << *i << endl;
  }
  {
    auto i = rng::find( v, 10 ); //1 2 3 4 5 6
    if (i == rng::end(v) ) { 
      cout << "didn't find 10" << endl; 
    } 
  }
  {
    auto i = rng::find_if( v, is_six ); 
    if (i != rng::end(v) ) { 
      cout << "*i: " << *i << endl;
    }
  }
  {
    auto i = rng::find_if_not( v, is_six ); 
    if (i != rng::end(v) ) { 
      cout << "*i: " << *i << endl;
    }
  }
  {
    auto i = rng::find( v, 6 );
    i++;
    if (i != rng::end(v) ) { 
      cout << "*i after ++ (2 expected): " << *i;
    }
  }

  cout << endl << "array:    ";

  array<int, 6> a { 6, 2, 3, 4, 5, 1 };
  {
    auto i = rng::find( a, 6 ); 
    if (i != rng::end(a)) {
      cout << "*i: " << *i;
    }
  }
  cout << endl << "list:     ";

  list<int> li { 6, 2, 3, 4, 5, 1 };
  {
    auto i = rng::find( li, 6 ); 
    if (i != rng::end(li)) {
      cout << "*i: " << *i;
    }
  }

  cout << endl << "fwd_list: ";

  forward_list<int> fl { 6, 2, 3, 4, 5, 1 };
  {
    auto i = rng::find( fl, 4 );
    if (i != rng::end(fl)) {
      cout << "*i: " << *i;
    }
  }

  cout << endl << "deque:    ";
  
  deque<int> d { 6 , 2, 3, 4, 5, 1 };
  {
    auto i = rng::find( d, 6 ); 
    if (i != rng::end(d)) {
      cout << "*i: " << *i;
    }
  }
  cout << endl;

}

