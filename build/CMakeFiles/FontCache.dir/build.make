# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/samuel/Desktop/Own Programming/Sudoku"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/samuel/Desktop/Own Programming/Sudoku/build"

# Include any dependencies generated for this target.
include CMakeFiles/FontCache.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FontCache.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FontCache.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FontCache.dir/flags.make

CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o: CMakeFiles/FontCache.dir/flags.make
CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o: /home/samuel/Desktop/Own\ Programming/Sudoku/src/SDL_FontCache/SDL_FontCache.c
CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o: CMakeFiles/FontCache.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/samuel/Desktop/Own Programming/Sudoku/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o -MF CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o.d -o CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o -c "/home/samuel/Desktop/Own Programming/Sudoku/src/SDL_FontCache/SDL_FontCache.c"

CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/samuel/Desktop/Own Programming/Sudoku/src/SDL_FontCache/SDL_FontCache.c" > CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.i

CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/samuel/Desktop/Own Programming/Sudoku/src/SDL_FontCache/SDL_FontCache.c" -o CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.s

# Object files for target FontCache
FontCache_OBJECTS = \
"CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o"

# External object files for target FontCache
FontCache_EXTERNAL_OBJECTS =

libFontCache.a: CMakeFiles/FontCache.dir/src/SDL_FontCache/SDL_FontCache.c.o
libFontCache.a: CMakeFiles/FontCache.dir/build.make
libFontCache.a: CMakeFiles/FontCache.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/samuel/Desktop/Own Programming/Sudoku/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libFontCache.a"
	$(CMAKE_COMMAND) -P CMakeFiles/FontCache.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FontCache.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FontCache.dir/build: libFontCache.a
.PHONY : CMakeFiles/FontCache.dir/build

CMakeFiles/FontCache.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FontCache.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FontCache.dir/clean

CMakeFiles/FontCache.dir/depend:
	cd "/home/samuel/Desktop/Own Programming/Sudoku/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/samuel/Desktop/Own Programming/Sudoku" "/home/samuel/Desktop/Own Programming/Sudoku" "/home/samuel/Desktop/Own Programming/Sudoku/build" "/home/samuel/Desktop/Own Programming/Sudoku/build" "/home/samuel/Desktop/Own Programming/Sudoku/build/CMakeFiles/FontCache.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/FontCache.dir/depend

