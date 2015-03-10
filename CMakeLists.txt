cmake_minimum_required (VERSION 2.8)
project (rfm22-wrapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories (
	${PROJECT_SOURCE_DIR}/include
)

add_subdirectory (src)

add_executable (rfm22-client rfm22-client.cpp)
target_link_libraries (rfm22-client rfm22)

add_executable (rfm22-server rfm22-server.cpp)
target_link_libraries (rfm22-server rfm22)