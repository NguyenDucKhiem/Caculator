cmake_minimum_required(VERSION 3.7)
project(GraphicsProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Button.h
        Graphics.h
        Calculator2.0.h
        Calculator3.0.h
        History.h
        LinkedList.h
        Mode.h
        Posfix.h
        test.cpp)

add_executable(GraphicsProject ${SOURCE_FILES})