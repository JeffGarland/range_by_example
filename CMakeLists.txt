# see run_cmake.sh
#required parms are RANGE_INCLUDE path
project (rbe)
cmake_minimum_required(VERSION 2.8)


include_directories(${RANGE_INCLUDE})

#probably not required for most
add_definitions( -std=c++17 )

add_executable( 01_hello 01_hello.cpp )
add_executable( 02_foreach_sequence 02_foreach_sequence.cpp )
add_executable( 03_foreach_assoc 03_foreach_assoc.cpp )
add_executable( 04_foreach_string 04_foreach_string.cpp )
add_executable( 04_count 04_count.cpp )
add_executable( 05_count_if 05_count_if.cpp )
add_executable( 06_all_any_none 06_all_any_none.cpp )
add_executable( 10_is_sorted 10_is_sorted.cpp )
add_executable( 11_max_min 11_max_min.cpp )
#add_executable( 13_sort 13_sort.cpp )

add_executable( 30_adjacent_find 30_adjacent_find.cpp )

add_executable( 50_zip 50_zip.cpp )


