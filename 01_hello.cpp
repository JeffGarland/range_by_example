#include <range/v3/all.hpp>  //get everything
namespace rng = ranges::v3;  //easy access

#include <iostream>
#include <string>
using namespace std;

int main() {

  string s { "hello" };

  //output: h e l l o
  rng::for_each( s, [](char c){ cout << c << " "; });

  cout << endl;
}
