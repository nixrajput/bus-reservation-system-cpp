cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(BusReservationSystem VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(BusReservationSystem src/main.cpp)

# Include directories if needed
include_directories(${PROJECT_SOURCE_DIR}/src)

# Link libraries if needed
# target_link_libraries(BusReservationSystem <library_name>)
