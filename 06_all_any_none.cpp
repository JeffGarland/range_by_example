/* output
vector: 6 2 3 4 5 6 
vector any is_six: true
vector all is_six: false
vector none of is_six: false
*/

#include <range/v3/algorithm/all_of.hpp>   //specific includes
#include <range/v3/algorithm/any_of.hpp>  
#include <range/v3/algorithm/none_of.hpp>  
#include <range/v3/algorithm/for_each.hpp> 
namespace rng = ranges::v3;

#include <vector>
#include <iostream>
using namespace std;


int main() {

  cout << "vector: ";
  auto print  = [](int i)         { cout << i << " "; };
  vector<int> v { 6, 2, 3, 4, 5, 6 };
  rng::for_each( v, print ); 
  cout << endl;
  
  auto is_six = [](int i) -> bool { return i == 6; };

  if (rng::any_of( v, is_six ))   {
    cout << "vector any is_six: true" << endl; 
  };
  if (!rng::all_of( v, is_six )) { 
    cout << "vector all is_six: false" << endl; 
  };
  if (!rng::none_of( v, is_six )) { 
    cout << "vector none of is_six: false" << endl; 
  };
  
}


