# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build

# Include any dependencies generated for this target.
include CMakeFiles/my_qt_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_qt_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_qt_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_qt_project.dir/flags.make

__/Headers/moc_Mainwindow.cpp: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Headers/Mainwindow.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating __/Headers/moc_Mainwindow.cpp"
	cd /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/__/Headers && /opt/homebrew/opt/qt/share/qt/libexec/moc @/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/__/Headers/moc_Mainwindow.cpp_parameters

CMakeFiles/my_qt_project.dir/Shop.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Shop.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Shop.cpp
CMakeFiles/my_qt_project.dir/Shop.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_qt_project.dir/Shop.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Shop.cpp.o -MF CMakeFiles/my_qt_project.dir/Shop.cpp.o.d -o CMakeFiles/my_qt_project.dir/Shop.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Shop.cpp

CMakeFiles/my_qt_project.dir/Shop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Shop.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Shop.cpp > CMakeFiles/my_qt_project.dir/Shop.cpp.i

CMakeFiles/my_qt_project.dir/Shop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Shop.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Shop.cpp -o CMakeFiles/my_qt_project.dir/Shop.cpp.s

CMakeFiles/my_qt_project.dir/Sale.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Sale.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Sale.cpp
CMakeFiles/my_qt_project.dir/Sale.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_qt_project.dir/Sale.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Sale.cpp.o -MF CMakeFiles/my_qt_project.dir/Sale.cpp.o.d -o CMakeFiles/my_qt_project.dir/Sale.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Sale.cpp

CMakeFiles/my_qt_project.dir/Sale.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Sale.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Sale.cpp > CMakeFiles/my_qt_project.dir/Sale.cpp.i

CMakeFiles/my_qt_project.dir/Sale.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Sale.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Sale.cpp -o CMakeFiles/my_qt_project.dir/Sale.cpp.s

CMakeFiles/my_qt_project.dir/Product.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Product.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Product.cpp
CMakeFiles/my_qt_project.dir/Product.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_qt_project.dir/Product.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Product.cpp.o -MF CMakeFiles/my_qt_project.dir/Product.cpp.o.d -o CMakeFiles/my_qt_project.dir/Product.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Product.cpp

CMakeFiles/my_qt_project.dir/Product.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Product.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Product.cpp > CMakeFiles/my_qt_project.dir/Product.cpp.i

CMakeFiles/my_qt_project.dir/Product.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Product.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Product.cpp -o CMakeFiles/my_qt_project.dir/Product.cpp.s

CMakeFiles/my_qt_project.dir/Person.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Person.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Person.cpp
CMakeFiles/my_qt_project.dir/Person.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_qt_project.dir/Person.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Person.cpp.o -MF CMakeFiles/my_qt_project.dir/Person.cpp.o.d -o CMakeFiles/my_qt_project.dir/Person.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Person.cpp

CMakeFiles/my_qt_project.dir/Person.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Person.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Person.cpp > CMakeFiles/my_qt_project.dir/Person.cpp.i

CMakeFiles/my_qt_project.dir/Person.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Person.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Person.cpp -o CMakeFiles/my_qt_project.dir/Person.cpp.s

CMakeFiles/my_qt_project.dir/Seller.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Seller.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Seller.cpp
CMakeFiles/my_qt_project.dir/Seller.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_qt_project.dir/Seller.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Seller.cpp.o -MF CMakeFiles/my_qt_project.dir/Seller.cpp.o.d -o CMakeFiles/my_qt_project.dir/Seller.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Seller.cpp

CMakeFiles/my_qt_project.dir/Seller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Seller.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Seller.cpp > CMakeFiles/my_qt_project.dir/Seller.cpp.i

CMakeFiles/my_qt_project.dir/Seller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Seller.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Seller.cpp -o CMakeFiles/my_qt_project.dir/Seller.cpp.s

CMakeFiles/my_qt_project.dir/Manager.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Manager.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Manager.cpp
CMakeFiles/my_qt_project.dir/Manager.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_qt_project.dir/Manager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Manager.cpp.o -MF CMakeFiles/my_qt_project.dir/Manager.cpp.o.d -o CMakeFiles/my_qt_project.dir/Manager.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Manager.cpp

CMakeFiles/my_qt_project.dir/Manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Manager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Manager.cpp > CMakeFiles/my_qt_project.dir/Manager.cpp.i

CMakeFiles/my_qt_project.dir/Manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Manager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Manager.cpp -o CMakeFiles/my_qt_project.dir/Manager.cpp.s

CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/AdminSeller.cpp
CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o -MF CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o.d -o CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/AdminSeller.cpp

CMakeFiles/my_qt_project.dir/AdminSeller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/AdminSeller.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/AdminSeller.cpp > CMakeFiles/my_qt_project.dir/AdminSeller.cpp.i

CMakeFiles/my_qt_project.dir/AdminSeller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/AdminSeller.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/AdminSeller.cpp -o CMakeFiles/my_qt_project.dir/AdminSeller.cpp.s

CMakeFiles/my_qt_project.dir/main.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/main.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/main.cpp
CMakeFiles/my_qt_project.dir/main.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/my_qt_project.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/main.cpp.o -MF CMakeFiles/my_qt_project.dir/main.cpp.o.d -o CMakeFiles/my_qt_project.dir/main.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/main.cpp

CMakeFiles/my_qt_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/main.cpp > CMakeFiles/my_qt_project.dir/main.cpp.i

CMakeFiles/my_qt_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/main.cpp -o CMakeFiles/my_qt_project.dir/main.cpp.s

CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o: /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Mainwindow.cpp
CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o -MF CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o.d -o CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Mainwindow.cpp

CMakeFiles/my_qt_project.dir/Mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/Mainwindow.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Mainwindow.cpp > CMakeFiles/my_qt_project.dir/Mainwindow.cpp.i

CMakeFiles/my_qt_project.dir/Mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/Mainwindow.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/Mainwindow.cpp -o CMakeFiles/my_qt_project.dir/Mainwindow.cpp.s

CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o: CMakeFiles/my_qt_project.dir/flags.make
CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o: __/Headers/moc_Mainwindow.cpp
CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o: CMakeFiles/my_qt_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o -MF CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o.d -o CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o -c /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/__/Headers/moc_Mainwindow.cpp

CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/__/Headers/moc_Mainwindow.cpp > CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.i

CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/__/Headers/moc_Mainwindow.cpp -o CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.s

# Object files for target my_qt_project
my_qt_project_OBJECTS = \
"CMakeFiles/my_qt_project.dir/Shop.cpp.o" \
"CMakeFiles/my_qt_project.dir/Sale.cpp.o" \
"CMakeFiles/my_qt_project.dir/Product.cpp.o" \
"CMakeFiles/my_qt_project.dir/Person.cpp.o" \
"CMakeFiles/my_qt_project.dir/Seller.cpp.o" \
"CMakeFiles/my_qt_project.dir/Manager.cpp.o" \
"CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o" \
"CMakeFiles/my_qt_project.dir/main.cpp.o" \
"CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o" \
"CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o"

# External object files for target my_qt_project
my_qt_project_EXTERNAL_OBJECTS =

my_qt_project: CMakeFiles/my_qt_project.dir/Shop.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/Sale.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/Product.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/Person.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/Seller.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/Manager.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/AdminSeller.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/main.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/Mainwindow.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/__/Headers/moc_Mainwindow.cpp.o
my_qt_project: CMakeFiles/my_qt_project.dir/build.make
my_qt_project: /opt/homebrew/opt/qt/lib/QtWidgets.framework/Versions/A/QtWidgets
my_qt_project: /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/lib/libsqlite3.tbd
my_qt_project: /opt/homebrew/opt/qt/lib/QtGui.framework/Versions/A/QtGui
my_qt_project: /opt/homebrew/opt/qt/lib/QtCore.framework/Versions/A/QtCore
my_qt_project: CMakeFiles/my_qt_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable my_qt_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_qt_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_qt_project.dir/build: my_qt_project
.PHONY : CMakeFiles/my_qt_project.dir/build

CMakeFiles/my_qt_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_qt_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_qt_project.dir/clean

CMakeFiles/my_qt_project.dir/depend: __/Headers/moc_Mainwindow.cpp
	cd /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build /Users/nnelkane/Downloads/Study/PonLHL/Yaskevich/Source/build/CMakeFiles/my_qt_project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/my_qt_project.dir/depend

