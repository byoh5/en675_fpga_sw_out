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

# Include any dependencies generated for this target.
include Source/core/shared/CMakeFiles/core.elf.dir/depend.make

# Include the progress variables for this target.
include Source/core/shared/CMakeFiles/core.elf.dir/progress.make

# Include the compile flags for this target's objects.
include Source/core/shared/CMakeFiles/core.elf.dir/flags.make

Source/core/shared/CMakeFiles/core.elf.dir/boot.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/boot.c.obj: ../Source/core/shared/boot.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/boot.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\boot.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\boot.c

Source/core/shared/CMakeFiles/core.elf.dir/boot.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/boot.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\boot.c > CMakeFiles\core.elf.dir\boot.c.i

Source/core/shared/CMakeFiles/core.elf.dir/boot.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/boot.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\boot.c -o CMakeFiles\core.elf.dir\boot.c.s

Source/core/shared/CMakeFiles/core.elf.dir/exbl.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/exbl.c.obj: ../Source/core/shared/exbl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/exbl.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\exbl.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\exbl.c

Source/core/shared/CMakeFiles/core.elf.dir/exbl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/exbl.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\exbl.c > CMakeFiles\core.elf.dir\exbl.c.i

Source/core/shared/CMakeFiles/core.elf.dir/exbl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/exbl.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\exbl.c -o CMakeFiles\core.elf.dir\exbl.c.s

Source/core/shared/CMakeFiles/core.elf.dir/msg.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/msg.c.obj: ../Source/core/shared/msg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/msg.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\msg.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\msg.c

Source/core/shared/CMakeFiles/core.elf.dir/msg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/msg.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\msg.c > CMakeFiles\core.elf.dir\msg.c.i

Source/core/shared/CMakeFiles/core.elf.dir/msg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/msg.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\msg.c -o CMakeFiles\core.elf.dir\msg.c.s

Source/core/shared/CMakeFiles/core.elf.dir/user.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/user.c.obj: ../Source/core/shared/user.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/user.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\user.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\user.c

Source/core/shared/CMakeFiles/core.elf.dir/user.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/user.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\user.c > CMakeFiles\core.elf.dir\user.c.i

Source/core/shared/CMakeFiles/core.elf.dir/user.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/user.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\user.c -o CMakeFiles\core.elf.dir\user.c.s

Source/core/shared/CMakeFiles/core.elf.dir/mentry.S.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/mentry.S.obj: ../Source/core/shared/mentry.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building ASM object Source/core/shared/CMakeFiles/core.elf.dir/mentry.S.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles\core.elf.dir\mentry.S.obj -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\mentry.S

Source/core/shared/CMakeFiles/core.elf.dir/test/test_nonos.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/test/test_nonos.c.obj: ../Source/core/shared/test/test_nonos.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/test/test_nonos.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\test\test_nonos.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_nonos.c

Source/core/shared/CMakeFiles/core.elf.dir/test/test_nonos.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/test/test_nonos.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_nonos.c > CMakeFiles\core.elf.dir\test\test_nonos.c.i

Source/core/shared/CMakeFiles/core.elf.dir/test/test_nonos.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/test/test_nonos.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_nonos.c -o CMakeFiles\core.elf.dir\test\test_nonos.c.s

Source/core/shared/CMakeFiles/core.elf.dir/test/test_dma.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/test/test_dma.c.obj: ../Source/core/shared/test/test_dma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/test/test_dma.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\test\test_dma.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_dma.c

Source/core/shared/CMakeFiles/core.elf.dir/test/test_dma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/test/test_dma.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_dma.c > CMakeFiles\core.elf.dir\test\test_dma.c.i

Source/core/shared/CMakeFiles/core.elf.dir/test/test_dma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/test/test_dma.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_dma.c -o CMakeFiles\core.elf.dir\test\test_dma.c.s

Source/core/shared/CMakeFiles/core.elf.dir/test/test_eth.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/test/test_eth.c.obj: ../Source/core/shared/test/test_eth.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/test/test_eth.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\test\test_eth.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_eth.c

Source/core/shared/CMakeFiles/core.elf.dir/test/test_eth.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/test/test_eth.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_eth.c > CMakeFiles\core.elf.dir\test\test_eth.c.i

Source/core/shared/CMakeFiles/core.elf.dir/test/test_eth.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/test/test_eth.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_eth.c -o CMakeFiles\core.elf.dir\test\test_eth.c.s

Source/core/shared/CMakeFiles/core.elf.dir/test/test_sdio.c.obj: Source/core/shared/CMakeFiles/core.elf.dir/flags.make
Source/core/shared/CMakeFiles/core.elf.dir/test/test_sdio.c.obj: ../Source/core/shared/test/test_sdio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object Source/core/shared/CMakeFiles/core.elf.dir/test/test_sdio.c.obj"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\core.elf.dir\test\test_sdio.c.obj   -c D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_sdio.c

Source/core/shared/CMakeFiles/core.elf.dir/test/test_sdio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core.elf.dir/test/test_sdio.c.i"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_sdio.c > CMakeFiles\core.elf.dir\test\test_sdio.c.i

Source/core/shared/CMakeFiles/core.elf.dir/test/test_sdio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core.elf.dir/test/test_sdio.c.s"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && D:\DEV_2020\en675\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-w64-mingw32\bin\riscv64-unknown-elf-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared\test\test_sdio.c -o CMakeFiles\core.elf.dir\test\test_sdio.c.s

# Object files for target core.elf
core_elf_OBJECTS = \
"CMakeFiles/core.elf.dir/boot.c.obj" \
"CMakeFiles/core.elf.dir/exbl.c.obj" \
"CMakeFiles/core.elf.dir/msg.c.obj" \
"CMakeFiles/core.elf.dir/user.c.obj" \
"CMakeFiles/core.elf.dir/mentry.S.obj" \
"CMakeFiles/core.elf.dir/test/test_nonos.c.obj" \
"CMakeFiles/core.elf.dir/test/test_dma.c.obj" \
"CMakeFiles/core.elf.dir/test/test_eth.c.obj" \
"CMakeFiles/core.elf.dir/test/test_sdio.c.obj"

# External object files for target core.elf
core_elf_EXTERNAL_OBJECTS =

core.elf: Source/core/shared/CMakeFiles/core.elf.dir/boot.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/exbl.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/msg.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/user.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/mentry.S.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/test/test_nonos.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/test/test_dma.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/test/test_eth.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/test/test_sdio.c.obj
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/build.make
core.elf: lib/libcore0.a
core.elf: lib/libcore1.a
core.elf: lib/libcore2.a
core.elf: lib/libcore3.a
core.elf: lib/libfatfs.a
core.elf: lib/liblwip.a
core.elf: lib/libfreertos.a
core.elf: lib/libdev.a
core.elf: Source/core/shared/CMakeFiles/core.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable ..\..\..\core.elf"
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\core.elf.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Source/core/shared/CMakeFiles/core.elf.dir/build: core.elf

.PHONY : Source/core/shared/CMakeFiles/core.elf.dir/build

Source/core/shared/CMakeFiles/core.elf.dir/clean:
	cd /d D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared && $(CMAKE_COMMAND) -P CMakeFiles\core.elf.dir\cmake_clean.cmake
.PHONY : Source/core/shared/CMakeFiles/core.elf.dir/clean

Source/core/shared/CMakeFiles/core.elf.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807 D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Source\core\shared D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared D:\DEV_2020\openedge\en675_f\en675_351t\IITP_NPU_MJS_20200807\Debug\Source\core\shared\CMakeFiles\core.elf.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Source/core/shared/CMakeFiles/core.elf.dir/depend
