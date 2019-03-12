cmake_minimum_required(VERSION 3.9)
project(zaawansowany_cpp)

set(CMAKE_CXX_STANDARD 11)

#add_executable(zaawansowany_cpp main.cpp zestaw1/main.cpp)
add_executable(zaawansowany_cpp zestaw2/main.cpp zestaw2/main.cpp zestaw2/Employee.hpp zestaw2/Engineer.hpp zestaw2/Seller.hpp)