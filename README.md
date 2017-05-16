# range_by_example
range v3 example code

The intent of this project is to make example code for Eric Niebler's [range v3 library]( https://ericniebler.github.io/range-v3/).  A host of basic information can be found on the [range v3 github](https://github.com/ericniebler/range-v3).


In general this code is written to c++17 so a modern C++ compiler is required. To date usage is primarily pre-release gcc-7.

## Why Ranges?

Simpler more elegant code. Much detail in the [standard library proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4128.html).

## Hello Ranges!

```c++

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
```

## Organization

The examples are largely divided into 2 main groups -- algorithms and views. 

