# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug

# Utility rule file for create_binary.

# Include the progress variables for this target.
include CMakeFiles/create_binary.dir/progress.make

CMakeFiles/create_binary: core.elf
	D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-objcopy.exe -O binary core.elf core.bin
	copy /b boot.bin + core.bin EN675.bin

create_binary: CMakeFiles/create_binary
create_binary: CMakeFiles/create_binary.dir/build.make

.PHONY : create_binary

# Rule to build all files generated by this target.
CMakeFiles/create_binary.dir/build: create_binary

.PHONY : CMakeFiles/create_binary.dir/build

CMakeFiles/create_binary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\create_binary.dir\cmake_clean.cmake
.PHONY : CMakeFiles/create_binary.dir/clean

CMakeFiles/create_binary.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807 D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807 D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles\create_binary.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/create_binary.dir/depend

