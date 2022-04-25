cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)
project (booking_problem)
file(GLOB SRCSAPP ./*.cpp)
file(GLOB SRCSLIB ./*.h)
add_executable( ${PROJECT_NAME}
 ${SRCSAPP}
 ${SRCSLIB} )
