
#include <range/v3/all.hpp>  // get everything
namespace rng = ranges::v3;  // easy access
namespace view = rng::view;  // easy access

#include <iostream>
#include <random>
using namespace std;


int main() {

  // some test data
  auto triangle_wave = {0., 1., 2., 1., 0., -1., -2., -1., 0.};

  // `mean` computes the average value of a given range
  auto mean = [](auto const& range) {
    using value_t = rng::range_value_type_t<decltype(range)>;
    return rng::accumulate(range, value_t{}) / value_t(rng::size(range));
  };


  cout << "\n--- Sliding window over range creates a range of ranges ---" << endl;
  rng::copy( triangle_wave
           | view::sliding(3)
           , rng::ostream_iterator(cout, "\n")
           );

 

  cout << "\n--- Moving average with win length of 3 ---" << endl;
  rng::transform( triangle_wave
                | view::sliding(3)
                , rng::ostream_iterator(cout, ", ")
                , mean
                );

  cout << endl;


  cout << "\n--- Same thing using copy algorithm and transform view ---" << endl;
  rng::copy( triangle_wave
           | view::sliding(3)
           | view::transform(mean)
           , rng::ostream_iterator(cout, ", ")
           );

  cout << endl;


  cout << "\n--- A sparse moving average, i.e. dropping every other frame ---" << endl;
  rng::copy( triangle_wave
           | view::sliding(3)       // moving window
           | view::stride(2)        // drop every second frame
           | view::transform(mean)  // compute mean value for given range
           , rng::ostream_iterator(cout, ", ")
           );

  cout << endl;

  cout << "\n--- Same thing but downsampling after the transform ---" << endl;
  rng::copy( triangle_wave
           | view::sliding(3)       // moving window
           | view::transform(mean)  // compute mean value for given range
                                    // Because views are lazy we can downsample after the transform.
           | view::stride(2)        // drop every second frame
                                    // The dropped values will never get computed in the first place.
           , rng::ostream_iterator(cout, ", ")
           );

  cout << endl;



  cout << "\n--- Generate some noise and filter it with a moving average ---" << endl;

  // Let's make a custom range view `windowing` that abstracts
  // a moving window with a length and a hop size.
  auto windowing = [](size_t len, size_t hop)
  {
    return view::sliding(len) | view::stride(hop);
  };


  // ...and use it to filter a range of random numbers...

  // view::generate let's us build a lazy range that produces random values
  auto noise_gen = view::generate(
    [ rnd_gen = mt19937{}
    , dist = normal_distribution<>{5,2} ]() mutable {
      return dist(rnd_gen);
    }
  );

  // Since a generate view is single pass we cannot use it with our
  // windowing view adaptor which requires at least a forward range.
  // So we copy it into a vector.

  vector<double> noise = noise_gen        // This generator is an infinite range...
                       | view::take(50)   // so we only take some values from it...
                       | rng::copy;       // and copy them eagerly into a vector.

  rng::copy( noise                              // Now we can take the random values...
           | windowing(3,2)                     // window it into overlapping chunks...
           | view::transform(mean)              // take the mean value of each chunk...
           , rng::ostream_iterator(cout, ", ")  // and send it to cout.
           );

  cout << endl;
}
