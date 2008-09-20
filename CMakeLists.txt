project(b2 C CXX)

cmake_minimum_required(VERSION 2.4)

file(GLOB SRCS *.cpp)
add_executable(b2 WIN32 MACOSX_BUNDLE ${SRCS})

find_package(wxWidgets REQUIRED base core xml)
include(${wxWidgets_USE_FILE})
include_directories(${wxWidgets_INCLUDE_DIRS})
link_directories(${wxWidgets_LIBRARY_DIRS})

target_link_libraries(b2 ${wxWidgets_LIBRARIES})
