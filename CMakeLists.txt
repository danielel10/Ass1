cmake_minimum_required(VERSION 3.20)
project(Ass1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ass1 src/main.cpp src/Studio.cpp include/Studio.h src/Trainer.cpp src/Workout.cpp include/Workout.h include/Studio.h)
