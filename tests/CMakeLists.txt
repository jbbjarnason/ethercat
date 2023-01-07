cmake_minimum_required(VERSION 3.20)
project(Ethercat_tests)

add_executable(ec_tests test_pack.cpp)

if(PROJECT_IS_TOP_LEVEL)
  # todo vcpkg
  find_package(asio CONFIG REQUIRED)
  find_package(fmt CONFIG REQUIRED)
  find_package(Boost REQUIRED)
endif()

# todo inherit from some other target
target_link_libraries(ec_tests PRIVATE fmt::fmt asio::asio Boost::boost)
target_include_directories(ec_tests PUBLIC ../include/public PRIVATE ../include)
