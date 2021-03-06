# Copyright: (C) 2011 IITRBCS
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.8.9)

enable_testing()

find_package(YARP REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
include(YarpIDL)

# Test using yarp_idl_to_dir
set(generated_libs_dir "${CMAKE_CURRENT_BINARY_DIR}")
yarp_idl_to_dir(demo.thrift ${generated_libs_dir} S1 H1 I1)
yarp_idl_to_dir(namespaced.thrift ${generated_libs_dir} S2 H2 I2)
yarp_idl_to_dir(objects3D.thrift ${generated_libs_dir} S3 H3 I3)
yarp_idl_to_dir(wrapping.thrift ${generated_libs_dir} S4 H4 I4)
yarp_idl_to_dir(sub/directory/clock_rpc.thrift ${generated_libs_dir} S5 H5 I5)
yarp_idl_to_dir(settings.thrift ${generated_libs_dir} S6 H6 I6)

include_directories(${generated_libs_dir}/include)
include_directories(${YARP_INCLUDE_DIRS})
add_executable(demo_test main.cpp ${S1} ${S2} ${S3} ${S4} ${S5} ${S6} ${H1} ${H2} ${H3} ${H4} ${H5} ${H6})
target_link_libraries(demo_test ${YARP_LIBRARIES})

add_test(demo_basic demo_test)


# Test using yarp_add_idl
set(IDL_FILES demo.thrift
              namespaced.thrift
              objects3D.thrift
              wrapping.thrift
              sub/directory/clock_rpc.thrift
              settings.thrift)
yarp_add_idl(IDL_GEN_FILES ${IDL_FILES})
include_directories(${YARP_INCLUDE_DIRS})
add_executable(demo_test2 main.cpp ${IDL_GEN_FILES})
target_link_libraries(demo_test2 ${YARP_LIBRARIES})

add_test(demo_basic2 demo_test2)
