# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\tysse\Documents\C++\Sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Sudoku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sudoku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sudoku.dir/flags.make

CMakeFiles/Sudoku.dir/main.cpp.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/main.cpp.obj: CMakeFiles/Sudoku.dir/includes_CXX.rsp
CMakeFiles/Sudoku.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Sudoku.dir/main.cpp.obj"
	C:\Users\tysse\Documents\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Sudoku.dir\main.cpp.obj -c C:\Users\tysse\Documents\C++\Sudoku\main.cpp

CMakeFiles/Sudoku.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sudoku.dir/main.cpp.i"
	C:\Users\tysse\Documents\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\tysse\Documents\C++\Sudoku\main.cpp > CMakeFiles\Sudoku.dir\main.cpp.i

CMakeFiles/Sudoku.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sudoku.dir/main.cpp.s"
	C:\Users\tysse\Documents\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\tysse\Documents\C++\Sudoku\main.cpp -o CMakeFiles\Sudoku.dir\main.cpp.s

CMakeFiles/Sudoku.dir/SudokuBoard.cpp.obj: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/SudokuBoard.cpp.obj: CMakeFiles/Sudoku.dir/includes_CXX.rsp
CMakeFiles/Sudoku.dir/SudokuBoard.cpp.obj: ../SudokuBoard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Sudoku.dir/SudokuBoard.cpp.obj"
	C:\Users\tysse\Documents\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Sudoku.dir\SudokuBoard.cpp.obj -c C:\Users\tysse\Documents\C++\Sudoku\SudokuBoard.cpp

CMakeFiles/Sudoku.dir/SudokuBoard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sudoku.dir/SudokuBoard.cpp.i"
	C:\Users\tysse\Documents\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\tysse\Documents\C++\Sudoku\SudokuBoard.cpp > CMakeFiles\Sudoku.dir\SudokuBoard.cpp.i

CMakeFiles/Sudoku.dir/SudokuBoard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sudoku.dir/SudokuBoard.cpp.s"
	C:\Users\tysse\Documents\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\tysse\Documents\C++\Sudoku\SudokuBoard.cpp -o CMakeFiles\Sudoku.dir\SudokuBoard.cpp.s

# Object files for target Sudoku
Sudoku_OBJECTS = \
"CMakeFiles/Sudoku.dir/main.cpp.obj" \
"CMakeFiles/Sudoku.dir/SudokuBoard.cpp.obj"

# External object files for target Sudoku
Sudoku_EXTERNAL_OBJECTS =

Sudoku.exe: CMakeFiles/Sudoku.dir/main.cpp.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/SudokuBoard.cpp.obj
Sudoku.exe: CMakeFiles/Sudoku.dir/build.make
Sudoku.exe: C:/Users/tysse/Documents/SFML/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib/libsfml-system-d.a
Sudoku.exe: C:/Users/tysse/Documents/SFML/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib/libsfml-window-d.a
Sudoku.exe: C:/Users/tysse/Documents/SFML/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib/libsfml-graphics-d.a
Sudoku.exe: C:/Users/tysse/Documents/SFML/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib/libsfml-network-d.a
Sudoku.exe: C:/Users/tysse/Documents/SFML/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib/libsfml-audio-d.a
Sudoku.exe: CMakeFiles/Sudoku.dir/linklibs.rsp
Sudoku.exe: CMakeFiles/Sudoku.dir/objects1.rsp
Sudoku.exe: CMakeFiles/Sudoku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Sudoku.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Sudoku.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sudoku.dir/build: Sudoku.exe

.PHONY : CMakeFiles/Sudoku.dir/build

CMakeFiles/Sudoku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Sudoku.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Sudoku.dir/clean

CMakeFiles/Sudoku.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\tysse\Documents\C++\Sudoku C:\Users\tysse\Documents\C++\Sudoku C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug C:\Users\tysse\Documents\C++\Sudoku\cmake-build-debug\CMakeFiles\Sudoku.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Sudoku.dir/depend

