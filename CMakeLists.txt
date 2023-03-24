cmake_minimum_required(VERSION 3.23)
project(mipt_Algorithms_Data_Structures)

set(CMAKE_CXX_STANDARD 14)

add_executable(mipt_Algorithms_Data_Structures
        main.cpp
        mdeque.h
        mheap.h
        mvector.h
        alg.h merge_sort.h)
