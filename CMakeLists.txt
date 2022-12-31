cmake_minimum_required(VERSION 3.20)
project(Ethercat)

add_executable(ec_master master.cpp)

find_package(asio CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(ec_master PRIVATE fmt::fmt asio::asio)