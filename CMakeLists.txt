cmake_minimum_required(VERSION 3.1..3.25)

project(machine_learning_S6)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES src/*)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(ml.out src/main.cpp)

target_link_libraries(ml.out ${PROJECT_NAME})

# Unitary testing
enable_testing()
message(STATUS "Adding tests : ")
file(GLOB_RECURSE TEST_FILES tests/*.cpp)
foreach(TEST_FILES ${TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_FILES} NAME_WE)
        add_executable(${TEST_NAME}.out ${TEST_FILES})
        target_link_libraries(${TEST_NAME}.out ${PROJECT_NAME})
        add_test(${TEST_NAME} ${TEST_NAME}.out)
        message("       - ${TEST_NAME}")        
endforeach()



  




