cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(se3313_lab3)

find_package(Threads REQUIRED)
find_package(Boost 1.58 REQUIRED ) # No libs required

set(CMAKE_CXX_STANDARD 11)

include_directories(SYSTEM ${Boost_INCLUDE_DIR}
                           lib/include)

include_directories(include/)

# In-lab

add_executable(lab src/lab.cpp)

# Assignment

add_library(report OBJECT include/report.hpp src/report.cpp)

add_executable(asn-writer src/writer.cpp $<TARGET_OBJECTS:report>)
target_link_libraries(asn-writer "${CMAKE_THREAD_LIBS_INIT}")

add_executable(asn-reader src/reader.cpp $<TARGET_OBJECTS:report>)
target_link_libraries(asn-reader "${CMAKE_THREAD_LIBS_INIT}")

install(TARGETS asn-writer RUNTIME DESTINATION bin)
install(TARGETS asn-reader RUNTIME DESTINATION bin)

