cmake_minimum_required(VERSION 3.1..3.25)

project(MachineLearningS6)

file(
        GLOB_RECURSE
        source_files
        src/*
)


add_executable(
        ${PROJECT_NAME}
        ${source_files}
)

