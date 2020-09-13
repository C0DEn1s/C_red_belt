cmake_minimum_required(VERSION 3.17)
project(expresses)

set(CMAKE_CXX_STANDARD 20)

add_executable(expresses expresses.cpp e_book.cpp hotel.cpp object_pool.cpp swap_sort_copy.cpp simple_vector.h simple_vector.cpp linked_list.cpp)