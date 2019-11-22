cmake_minimum_required(VERSION 2.8)

project(Pangolin_Show CXX)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV 3.0 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 2.4.3 QUIET)
   if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
   endif()
endif()

find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)

include_directories(${PROJECT_NAME} ${OpenCV_INCLUDE_DIRS} ${Pangolin_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(pangolin_show  src/pangolin_show.cpp)
target_link_libraries(pangolin_show ${OpenCV_LIBS} ${Pangolin_LIBRARIES} ${EIGEN3_LIBS})
