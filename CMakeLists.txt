cmake_minimum_required(VERSION 3.10)
project(my_project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp DecisionTreeClassifier.cpp DecisionTreeClassifier.h)
add_executable(myProject ${SOURCES})