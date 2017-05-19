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

In general examples will shorten code text by omitting includes and assuming the following:

```c++

#include <range/v3/all.hpp> //get everything 
namespace rng = ranges::v3; //easy access

#include <...various std library headers...>
using namespace std;

```

## Range Library Organization

The examples are largely divided into 2 main groups -- algorithms and views. 

## Algorithms

### for_each

Applies a function to each element of the range.  

[Full Example](02_foreach_sequence.cpp)

[Try it yourself](https://wandbox.org/permlink/MPRED5rGIuk3K7WD)

```c++
/* output
vector:   1 2 3 4 5 6 
array:    1 2 3 4 5 6 
list:     1 2 3 4 5 6 
fwd_list: 1 2 3 4 5 6 
deque:    1 2 3 4 5 6 
*/

#include <range/v3/algorithm/for_each.hpp>   //specific includes
//...includes omitted...

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
```

###  all_of, any_of, none_of

Tests a predicate against each element of the range returning a bool result.

[Full Example](06_all_any_none.cpp)

[Try it yourself](https://wandbox.org/permlink/Ks0DQv4wKHFt7AAi)

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
  //...printing vector omitted...
  
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

###  set_union, set_intersection

Computes the union or intersection of two sets (sorted ranges).

[Full Example](40_set_algos.cpp)

[Try it yourself](https://wandbox.org/permlink/lhOc3bWl2UYRMR3T)

```c++

/* output
set s1: 1 2 3 4 5 7
set s2: 1 2 3 4 6 8
union: 1 2 3 4 5 6 7 8
intersection: 1 2 3 4
*/

#include <range/v3/algorithm/set_algorithm.hpp>
//...standard includes omitted...

namespace rng = ranges::v3;  //easy access

void output(const vector<int>& range) {
  for (auto i : range) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {

  vector<int> s1 = {1, 2, 3, 4, 5, 7};
  cout << "set s1: ";
  output(s1);

  vector<int> s2 = {1, 2, 3, 4, 6, 8};
  cout << "set s2: ";
  output(s2);

  {
    vector<int> u;
    auto it = rng::set_union(
        s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), rng::back_inserter(u));
    cout << "union: ";
    output(u);
  }

  {
    vector<int> u;
    auto it = rng::set_intersection(
        s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), rng::back_inserter(u));
    cout << "intersection: ";
    output(u);
  }
}
```


## Views

### drop, drop_exactly, drop_while

Lazily remove elements from the beginning of a range.

```drop```: Given a source range and an integral count, return a range consisting of all but the first count elements from the source range, or an empty range if it has fewer elements.

```drop_exactly```: Given a source range and an integral count, return a range consisting of all but the first count elements from the source range. The source range must have at least that many elements.

```drop_while```: Remove elements from the front of a range that satisfy a unary predicate.

[Full Example](60_drop.cpp)

[Try it yourself](https://wandbox.org/permlink/rcDuZ9YT2iKxnlph)

```c++
/* output
vector: 6 2 3 4 5 6 
vector drop half: 4 5 6 
vector drop exactly one: 2 3 4 5 6 
vector drop leading evens: 3 4 5 6 
*/

int main() {

  auto print  = [](int i)         { cout << i << " "; };

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6 };
  rng::for_each(v, print); 
  cout << endl;
  
  cout << "vector drop half: ";
  auto last_half = rng::view::drop(v, v.size()/2);
  rng::for_each(last_half, print); 
  cout << endl;
  
  cout << "vector drop exactly one: ";
  auto dropped_1 = rng::view::drop(v, 1);
  rng::for_each(dropped_1, print); 
  cout << endl;

  cout << "vector drop leading evens: ";
  auto is_even = [](int i) { return i % 2 == 0; };
  auto after_leading_evens = rng::view::drop_while(v, is_even);
  rng::for_each(after_leading_evens, print); 
  cout << endl;
}
```

### stride

Lazily skip over elements in a range N elements per step.

Given a source range and an integral stride value, return a range consisting of every Nth element, starting with the first.

[Full Example](61_stride.cpp)

[Try it yourself](https://wandbox.org/permlink/AeWAPzPPNscTmGlM)

```c++
/* output
vector: 6 2 3 4 5 6 
vector every 3rd value: 6 4 
*/

int main() {
  auto print  = [](int i)         { cout << i << " "; };

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6, 7, 8, 9, 1, 0 };
  rng::for_each(v, print); 
  cout << endl;

  cout << "vector every 3rd value: ";
  auto strided = rng::view::stride(v, 3);
  rng::for_each(strided, print); 
  cout << endl;
}
```

## Range Composition

Ranges can be composed using the pipe (```|```) operator. 

### Values at even/odd indicies in a range

Values at even indicies can be viewed by using ```view::stride(2)``` to step (or stride) 2 indicies at a time. Like skipping a stairs when climbing stairs. To create a view of the values at odd indicies the first value in the source range must be dropped, then start striding.

[Full Example](62_even_odd_indicies.cpp)

[Try it yourself](https://wandbox.org/permlink/Rz3ug2K0I4JLzPmB)

```c++
/* output
vector: 6 2 3 4 5 6 7 8 9 1 0 
vector values at even indicies: 6 3 5 7 9 0 
vector values at odd indicies: 2 4 6 8 1 
*/

int main() {
  auto print  = [](int i)         { cout << i << " "; };

  cout << "vector: ";
  vector<int> v { 6, 2, 3, 4, 5, 6, 7, 8, 9, 1, 0 };
  rng::for_each(v, print); 
  cout << endl;

  cout << "vector values at even indicies: ";
  auto evens = rng::view::stride(v, 2);
  rng::for_each(evens, print); 
  cout << endl;

  cout << "vector values at odd indicies: ";
  auto odds = rng::view::drop_exactly(v, 1) | rng::view::stride(2);
  rng::for_each(odds, print); 
  cout << endl;
}
```