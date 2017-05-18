/* output
a _ s t r i n g 
A _ S T R I N G 
*/

#include <range/v3/algorithm/for_each.hpp>   //specific includes
namespace rng = ranges::v3;

#include <iostream>
#include <string>
using namespace std;

auto print =  [] (char c) { cout << c << " "; };

int main() {
  
  string s { "a_string" };
  rng::for_each( s, print );

  cout << endl;

  //modify the string in place
  rng::for_each( s , [](char& c) { c = std::toupper(c); } );
  rng::for_each( s, print );
  
  cout << endl;

}
