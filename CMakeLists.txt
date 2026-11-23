cmake_minimum_required(VERSION 3.10)

# Set the project name and version (read from the VERSION file)
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" APP_VERSION LIMIT_COUNT 1)
project(BusReservationSystem VERSION ${APP_VERSION})

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(BusReservationSystem src/main.cpp)

if(NOT MSVC)
  target_compile_options(BusReservationSystem PRIVATE -Wall -Wextra)
endif()

enable_testing()
add_test(NAME smoke COMMAND sh ${PROJECT_SOURCE_DIR}/test/smoke.sh $<TARGET_FILE:BusReservationSystem>)

# Include directories if needed
include_directories(${PROJECT_SOURCE_DIR}/src)

# Link libraries if needed
# target_link_libraries(BusReservationSystem <library_name>)
