set(CMAKE_SYSTEM_PROCESSOR x64)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS -stdlib=libc++) # todo switch to llvm when host is at least version 15
set(CMAKE_CXX_FLAGS -stdlib=libstdc++)
set(CMAKE_C_FLAGS "")
set(LINK_FLAGS -fuse-ld=lld)
set(STATIC_LIBRARY_FLAGS -fuse-ld=lld)
