cmake_minimum_required(VERSION 3.21)
project(SO_PROJETO C)


set(CMAKE_C_STANDARD 99)

add_executable(SO_PROJETO main.c src/myData.c src/myData.h src/objectives.c src/objectives.h  src/myDataTimeCount.c src/myDataTimeCount.h src/objectiveD.c src/objectiveD.h src/objectiveA_parte2.c src/objectiveA_parte2.h src/objectiveB_parte2.c src/objectiveB_parte2.h src/objectiveC_parte2.c src/objectiveC_parte2.h src/objectiveD_parte2.c src/objectiveD_parte2.h)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(SO_PROJETO PRIVATE Threads::Threads)