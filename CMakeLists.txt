cmake_minimum_required(VERSION 3.28)
project(space)

set(CMAKE_CXX_STANDARD 26)

find_package(OpenMP REQUIRED)


add_executable(space main.cpp
        Camera.cpp
        Camera.h
        Entities/Object.cpp
        Entities/Object.h
        Entities/World.cpp
        Entities/World.h
        Entities/SingleThreadWorld.cpp
        Entities/SingleThreadWorld.h
        Entities/MultiThreadWorld.cpp
        Entities/MultiThreadWorld.h
        misc/mpmc_queue.h
        misc/ext_math.cpp
        misc/ext_math.h
)

target_link_libraries(space OpenMP::OpenMP_CXX sfml-graphics sfml-window sfml-system)

