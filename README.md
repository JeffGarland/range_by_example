# range_by_example
range v3 example code

The intent of this project is to make example code for Eric Niebler's [range v3 library]( https://ericniebler.github.io/range-v3/).  A host of basic information can be found on the [range v3 github](https://github.com/ericniebler/range-v3).

In general this code is written to c++17 so a modern C++ compiler is required. To date usage is primarily pre-release gcc-7.

## Why Ranges?

Simpler more elegant code. Much detail in the [standard library proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4128.html).

## Hello Ranges!

```c++

#include <range/v3/all.hpp> //get everything 
namespace rng = ranges::v3; //easy access

#include <iostream>
#include <string>
using namespace std;

int main() {

   string s { "hello" };

  //output: h e l l o
  rng::for_each( s, [](char c){ cout << c << " "; });

  cout << endl;
}
```

## Example Conventions

In general examples will shorten code text by omiting includes and assuing the following:

```c++

#include <range/v3/all.hpp> //get everything 
namespace rng = ranges::v3; //easy access

#include <...various std library headers>
using namespace std;

```

## Range Library Organization

The examples are largely divided into 2 main groups -- algorithms and views. 

## Algorithms

### for_each

Applies a function to each element of the range.  


###  all_of, any_of, none_of

Tests a predicate against each element of the range returning a bool result.

[Full Example](../blob/master/06_all_any_none.cpp)

```c++

/* output
vector: 6 2 3 4 5 6 
vector any is_six: true
vector all is_six: false
vector none of is_six: false
*/

#include <range/v3/algorithm/all_of.hpp>   //specific includes
#include <range/v3/algorithm/any_of.hpp>  
#include <range/v3/algorithm/none_of.hpp>  
//...standard includes omitted...

int main() {

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6 };
  //...printing vector omitted..
  
  auto is_six = [](int i) -> bool { return i == 6; };

  if (rng::any_of( v, is_six ))  { 
     cout << "vector any is_six: true" << endl; 
  };
  if (!rng::all_of( v, is_six )) { 
     cout << "vector all is_six: false" << endl; 
  };
  if (!rng::none_of( v, is_six )) { 
     cout << "vector none of is_six: false" << endl; 
  };
  
}
```


## Views
