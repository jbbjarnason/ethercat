set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS "-stdlib=libc++")  # todo switch to llvm when host is at least version 15
set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")
set(CMAKE_C_FLAGS "")
set(LINK_FLAGS "-fuse-ld=lld")

set(ENV{CC} clang)
set(ENV{CXX} clang++)
set(ENV{CXXFLAGS} -stdlib=libstdc++)  # todo switch to llvm when host is at least version 15
set(ENV{CFLAGS} "")
set(ENV{LDFLAGS} -fuse-ld=lld)
