cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(se3313_lab3)

find_package(Threads REQUIRED)
find_package(Boost 1.58 REQUIRED date_time) # No libs required

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(SYSTEM ${Boost_INCLUDE_DIR}
                           lib/include)

include_directories(include/)

set(LAB3_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}" ${Boost_LIBRARIES})
link_directories(${Boost_LIBRARY_DIRS})

if(UNIX AND NOT APPLE)
    # Add librt if on Linux 
    list(APPEND LAB3_LIBRARIES rt)
endif()

# In-lab

add_executable(lab src/lab.cpp)
target_link_libraries(lab ${LAB3_LIBRARIES})

# Assignment

add_library(report OBJECT include/report.hpp src/report.cpp)

add_executable(asn-writer src/writer.cpp $<TARGET_OBJECTS:report>)
target_link_libraries(asn-writer ${LAB3_LIBRARIES})

add_executable(asn-reader src/reader.cpp $<TARGET_OBJECTS:report>)
target_link_libraries(asn-reader ${LAB3_LIBRARIES})

install(TARGETS asn-writer RUNTIME DESTINATION bin)
install(TARGETS asn-reader RUNTIME DESTINATION bin)

