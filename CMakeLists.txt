cmake_minimum_required(VERSION 3.24)
project(sudoku)

#Set compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set optimization level
set(CMAKE_CXX_FLAGS_RELEASE "-O3")



#add SMD and TTF library
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
add_library(FontCache
    src/SDL_FontCache/SDL_FontCache.h
    src/SDL_FontCache/SDL_FontCache.c
)

include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

#add executable
add_executable(sudoku main.cpp src/field.cpp)

#like the libraries
target_link_libraries(sudoku ${SDL2_LIBRARIES})
target_link_libraries(sudoku SDL2_ttf::SDL2_ttf)
target_link_libraries(sudoku FontCache)