cmake_minimum_required(VERSION 3.0)

project(joueurs)

find_package(Threads)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
add_compile_options(-Wall -Wpedantic)


set(SRCS
    joueur.cpp
    joueur_random.cpp
    joueur_manuel.cpp
    joueur_brutal_.cpp
    alphabeta_matthew.cpp
    )
    
set(HEADERS
    joueur.h
    joueur_random.h
    joueur_manuel.cpp
    joueur_brutal_.h
    alphabeta_matthew.h
    )

add_library(joueurs ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
