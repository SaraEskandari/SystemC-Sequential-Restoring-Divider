
cmake_minimum_required(VERSION 3.10)
project(SignedDividerProject)

set(SYSTEMC_HOME /opt/systemc)
set(SYSTEMC_INCLUDE_DIR ${SYSTEMC_HOME}/include)
set(SYSTEMC_LIBRARY_DIR ${SYSTEMC_HOME}/lib)

add_executable(SignedDivider
    DividerMain.cpp
    divider_signed_tb.cpp
)

target_include_directories(SignedDivider PRIVATE ${SYSTEMC_INCLUDE_DIR})
target_link_directories(SignedDivider PRIVATE ${SYSTEMC_LIBRARY_DIR})
target_link_libraries(SignedDivider PRIVATE systemc)
