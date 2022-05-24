cmake_minimum_required(VERSION 3.0)

project(Thumbnail)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

set(source_dir 
    src/genThumbnail.cpp)
add_executable(Thumbnail ${source_dir})

target_link_libraries(Thumbnail ${OpenCV_LIBS})