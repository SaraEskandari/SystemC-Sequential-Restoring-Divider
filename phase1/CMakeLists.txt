cmake_minimum_required(VERSION 3.10)
project(SignedDividerProject)

set(SYSTEMC_HOME /opt/systemc)
set(SYSTEMC_INCLUDE_DIR ${SYSTEMC_HOME}/include)
set(SYSTEMC_LIBRARY_DIR ${SYSTEMC_HOME}/lib)

# Add your executable and all related .cpp files here
add_executable(main_wrapper
    main_wrapper.cpp
    controler_divider_unsigned.cpp
    divider_signed_tb.cpp
    wrapper_divider_controler.cpp 
)

target_include_directories(main_wrapper PRIVATE ${SYSTEMC_INCLUDE_DIR})
target_link_directories(main_wrapper PRIVATE ${SYSTEMC_LIBRARY_DIR})
target_link_libraries(main_wrapper PRIVATE systemc)
