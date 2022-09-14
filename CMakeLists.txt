
cmake_minimum_required(VERSION 3.1)

project(ffclustering VERSION 1
    LANGUAGES CXX
)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FFCLUSTERING_SRC
    src/db.cpp
    src/cluster.cpp
	src/painter.cpp
    src/data.cpp
    src/compare.cpp
    src/clustering.cpp
    src/main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -O3 -DIL_STD -ldl")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -O3 -DIL_STD -ldl")

add_executable(${PROJECT_NAME}
    ${FFCLUSTERING_SRC}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} X11)
