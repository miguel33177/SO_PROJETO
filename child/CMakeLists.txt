cmake_minimum_required(VERSION 3.21)
project(child C)

set(CMAKE_C_STANDARD 99)

add_executable(child main.c src/myDataChild.c src/myDataChild.h src/objectiveB.c src/objectiveB.h src/objectiveC.c src/objectiveC.h src/objectiveD.c src/objectiveD.h)
