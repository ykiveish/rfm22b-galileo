include_directories (${PROJECT_SOURCE_DIR}/include)

add_library (rfm22 SHARED RF22.cpp)
target_link_libraries (rfm22 mraa)