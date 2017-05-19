/* output
1 
2 
3 Fizz
4 
5 Buzz
6 Fizz
7 
8 
9 Fizz
10 Buzz
11 
12 Fizz
13 
14 
15 FizzBuzz
16 
17 
18 Fizz
19 
20 Buzz
*/

// Pass your job interview with a dose of functional flair

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/cycle.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/zip.hpp>
namespace rng = ranges::v3;

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // define infinite ranges of "Fizz" and "Buzz" every 3 and 5 entries
    std::vector<std::string> fizz_data{"", "", "Fizz"};
    std::vector<std::string> buzz_data{"", "", "", "", "Buzz"};
    auto fizzes = rng::view::cycle(fizz_data);
    auto buzzes = rng::view::cycle(buzz_data);

    // an infinite range of associated integers
    auto counts = rng::view::ints(1);

    // zip the three ranges to become a single infinite range
    auto tuples = rng::view::zip(counts, fizzes, buzzes);

    // take a finite number of the result
    const int count = 20;
    auto tuples_fnt = rng::view::take(tuples, count);

    // iterate and print
    rng::for_each(tuples_fnt,
                  [](auto x) {
                      cout << get<0>(x) << " " << get<1>(x) << get<2>(x) << "\n";
                  });
}

