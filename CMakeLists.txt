cmake_minimum_required(VERSION 3.16.5)
project(EasyDelegateExample CXX)

set(CMAKE_CXX_STANDARD 17)

set(DELEGATE_EXAMPLE_SOURCE examples/DelegateExample.cpp)
add_executable(DELEGATE_EXAMPLE ${DELEGATE_EXAMPLE_SOURCE})

set(MULTI_DELEGATE_EXAMPLE_SOURCE examples/MultiDelegateExample.cpp)
add_executable(MULTI_DELEGATE_EXAMPLE ${MULTI_DELEGATE_EXAMPLE_SOURCE})

set(COMPILE_TIME_ANY_EXAMPLE_SOURCE examples/CompileTimeAnyExample.cpp)
add_executable(COMPILE_TIME_ANY_EXAMPLE ${COMPILE_TIME_ANY_EXAMPLE_SOURCE})

set(RUN_TIME_ANY_EXAMPLE_SOURCE examples/RuntimeAnyDelegateExample.cpp)
add_executable(RUN_TIME_ANY_EXAMPLE ${RUN_TIME_ANY_EXAMPLE_SOURCE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)