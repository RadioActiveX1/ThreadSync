cmake_minimum_required(VERSION 3.12)

project(MultithreadedDataProcessing)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the main executable
add_executable(multithreaded_app multithreaded_app.cpp)

# Find and link the required thread library
find_package(Threads REQUIRED)
target_link_libraries(multithreaded_app PRIVATE Threads::Threads)
