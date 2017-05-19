#include <range/v3/all.hpp>  // get everything
namespace rng = ranges::v3;  // easy access
namespace view = rng::view;  // easy access

#include <iostream>
using namespace std;


int main() {

  // To build a neural network we first need some basic linear algebra facilities.

  // ´matrix_view` constructs a range of ranges (2D range) over a given flat range.
  auto matrix_view = [](auto const& range, size_t num_cols) {
    return  range | view::chunk(num_cols);
  };

  // `sum` is an eager algorithm the does what it says.
  auto sum = [](auto const& range) {
    using value_t = rng::range_value_type_t<decltype(range)>;
    return rng::accumulate(range, value_t{});
  };

  // `add` adds two ranges lazily.
  auto add = [](auto const& r1, auto const& r2) {
    return view::zip_with( std::plus<>{}, r1, r2 );
  };

  // `dot` computes the dot product of two ranges
  auto dot = [sum](auto const& r1, auto const& r2) {
    return sum( view::zip_with( std::multiplies<>{}, r1, r2 ));
  };

  // `dot_mat` computes the dot product of a 2D-range (range of ranges) and a single range
  auto dot_mat = [dot](auto const& mat, auto const& vec) {
    return  mat | view::transform([dot,&vec](auto const row){
      return dot(row,vec);
    });
  };



  // Now let's build a little neural network layers...

  // `scale_add` mixes the input neurons with the given weights and adds a bias
  auto scale_add = [add,dot_mat](auto const& weights, auto const& biases) {
    return [=](auto const x) {
      return add(dot_mat(weights,x), biases);
    };
  };

  // `sigmoid` is a lazy view that does the nonlinear mapping of the outputs
  auto sigmoid = view::transform([](auto const& x) {
                   decltype(x) one = 1.;
                   return one / (one + std::exp(-x));
                 });

  // weights and biases for two layers, just some random numbers
  auto W1 = { -2., -.2, .8
            ,  1.,  0., -1. };

  auto b1 = { 1., 2., 3. };

  auto W2 = {  1., -0.3
            , -1.,  0.9 };

  auto b2 = { -1., 0.2 };


  // Now, construct the actual network...

  auto network =
  [ =
  , layer1 = scale_add(matrix_view(W1,3), b1)
  , layer2 = scale_add(matrix_view(W2,2), b2)
  ]
  (auto const& l0)
  {
    std::vector<double> l1 = layer1(l0) | sigmoid | rng::copy;
    std::vector<double> l2 = layer2(l1) | sigmoid | rng::copy;
    return l2;
  };


  // Run the network with some input and print the result

  auto input = {1., 0.3, 0.8};
  rng::copy( network(input), rng::ostream_iterator(cout, "\n"));
}


