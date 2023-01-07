cmake_minimum_required(VERSION 3.20)
project(Ethercat)

add_executable(ec_master master.cpp)

find_package(asio CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

target_link_libraries(ec_master PRIVATE fmt::fmt asio::asio Boost::boost)
target_include_directories(ec_master PUBLIC include/public PRIVATE include)

# todo tests option
add_subdirectory(tests)
