/* output
[
  5 0 6 
  0 1 0 
  2 0 0 
  0 3 0 
]
transposed:
[
  5 0 2 0 
  0 1 0 3 
  6 0 0 0 
]

[
  0 0 0 
  0 0 0 
  0 0 0 
]
transposed:
[
  0 0 0 
  0 0 0 
  0 0 0 
]

[
  1 
]
transposed:
[
  1 
]

[
  1 0 0 
  0 2 0 
  3 0 0 
]
transposed:
[
  1 0 3 
  0 2 0 
  0 0 0 
]

[
  1 0 0 
  0 2 3 
  0 0 0 
]
transposed:
[
  1 0 0 
  0 2 0 
  0 3 0 
]
*/

// Transpose a sparse matrix in CRS format
// contributed by Jeff Trull <edaskel@att.net>

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/single.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/tail.hpp>
#include <range/v3/view/repeat.hpp>
#include <range/v3/view/repeat_n.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/slice.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/empty.hpp>
#include <range/v3/view/any_view.hpp>
namespace rng = ranges::v3;

#include <iostream>
#include <vector>
using namespace std;

// utility function: adjacent_difference view
// range-v3 only provides adjacent_difference mutating algorithm at this time

template<typename Rng,
         typename Fn = std::minus<rng::range_value_type_t<Rng>>>
rng::any_view<rng::range_value_type_t<Rng>>
adj_diff_view(Rng r, Fn f = Fn()) {
  using namespace rng::view;

  if (rng::empty(r)) {
    return empty<rng::range_value_type_t<Rng>>();
  }

  return concat(take(r, 1),    // first element is unchanged
                // remainder is f() applied to adjacent elements
                  zip_with(f, tail(r), slice(r, 0, rng::end-1)));
}

// our sparse matrix type
template<typename Index=std::size_t, typename Value=double>
struct sparse_matrix_t {
  // See http://netlib.org/linalg/html_templates/node91.html
  Index         col_cnt;
  vector<Index> row_ptr;
  vector<Index> col_ind;
  vector<Value> val;
};

template<typename Index, typename Value>
ostream& operator<<(ostream& os, sparse_matrix_t<Index, Value> const& m) {
  os << "[\n";

  // take the row indices and produce a range of [start, end) pairs
  using namespace rng::view;
  auto row_starts = slice(m.row_ptr, 0, rng::end-1);
  auto row_ends   = tail(m.row_ptr);

  rng::for_each(zip(row_starts, row_ends),
                [&os, &m](auto row) {
                  // re-inflate the range of values in this row by inserting 0's

                  // first, extract the column indices and values of this row
                  auto col_ind = slice(m.col_ind, get<0>(row), get<1>(row));
                  auto val     = slice(m.val,     get<0>(row), get<1>(row));
                    
                  // expand the columns by inserting 0's

                  // calculate number of zeros preceding each value
                  auto zero_count = adj_diff_view(col_ind, [](Index a, Index b) { return a-b-1; });

                  // iterate over the nonzero values
                  auto row_values =
                    for_each(zip(zero_count, val),
                             [](auto zc_val) {
                               // construct sequence of 0's followed by the nonzero
                               return concat(repeat_n(Value{0.0}, get<0>(zc_val)),
                                             single(get<1>(zc_val)));
                             });

                  // pad out remaining columns with zeros
                  auto full_row = take(concat(row_values, repeat(Value{0.0})),
                                       m.col_cnt);

                  // print row
                  os << "  ";
                  rng::for_each(full_row, [&os](Value v) { os << v << " "; });
                  os << "\n";

                });

  os << "]\n";

  return os;

}

template<typename Index, typename Value>
sparse_matrix_t<Index, Value>
transpose(sparse_matrix_t<Index, Value> m) {
  using namespace rng::view;

  // create a range holding the current row indices (future column indices) of each value

  // first get the number of entries in each row
  auto nz_row_counts = adj_diff_view(tail(m.row_ptr));

  vector<Index> row_ind;
  // iterate over (row number, entry count) for each row
  row_ind = join(zip_with([](auto rowno, auto count) { return repeat_n(rowno, count); },
                          iota(Index{0}),
                          nz_row_counts));

  // sort a zip of (old row indices, old column indices, values)
  // by (old column indices, old row indices) to produce a column major order

  auto col_major_zip = zip(m.col_ind, row_ind, m.val);

  // stable_sort using just (old column indices) will also work here - need to investigate perf
  rng::sort(col_major_zip,
            [](auto a, auto b) { return tie(get<0>(a), get<1>(a)) < tie(get<0>(b), get<1>(b)); });

  // swap the sorted row indices into place as the new columns
  swap(m.col_ind, row_ind);

  // scan the new row indices to locate row boundaries
  auto row_ind_it = begin(row_ind);
  Index old_row_cnt = m.row_ptr.size() - 1;
  m.row_ptr = for_each(iota(Index{0}, m.col_cnt+1),
                       [&](Index row) {
                         row_ind_it = std::lower_bound(row_ind_it, row_ind.end(), row);
                         return single(distance(row_ind.begin(), row_ind_it));
                       });
  m.col_cnt = old_row_cnt;

  return m;

};

int main() {
  // a fairly ordinary sparse matrix
  sparse_matrix_t<> mat;
  mat.row_ptr = { 0, 2, 3, 4, 5 };
  mat.col_ind = { 0, 2, 1, 0, 1 };
  mat.val     = { 5, 6, 1, 2, 3 };
  mat.col_cnt = 3;
  cout << mat;

  sparse_matrix_t<> mat_transpose = transpose(std::move(mat));

  cout << "transposed:\n" << mat_transpose << "\n";

  // one that is all zeros (and 3x3)
  sparse_matrix_t<> zero;
  zero.row_ptr = { 0, 0, 0, 0 };
  zero.col_cnt = 3;
  cout << zero;
  cout << "transposed:\n" << transpose(zero) << "\n";

  // one with only one entry
  sparse_matrix_t<> one;
  one.row_ptr = { 0, 1 };
  one.col_ind = { 0 };
  one.val = { 1.0 };
  one.col_cnt = 1;
  cout << one;
  cout << "transposed:\n" << transpose(one) << "\n";

  // one with an empty column
  sparse_matrix_t<> empty_col;
  empty_col.row_ptr = { 0, 1, 2, 3 };
  empty_col.col_ind = { 0, 1, 0 };
  empty_col.val = { 1.0, 2.0, 3.0 };
  empty_col.col_cnt = 3;
  cout << empty_col;
  cout << "transposed:\n" << transpose(empty_col) << "\n";

  // one with an empty row
  sparse_matrix_t<> empty_row;
  empty_row.row_ptr = { 0, 1, 3, 3 };
  empty_row.col_ind = { 0, 1, 2 };
  empty_row.val = { 1.0, 2.0, 3.0 };
  empty_row.col_cnt = 3;
  cout << empty_row;
  cout << "transposed:\n" << transpose(empty_row) << "\n";


}
