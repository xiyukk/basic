# 这个cmake文件是错误的，不要使用它.
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Collect source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Set the output directory for the compiled executables
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/build")

# Create an executable for each source file
foreach(source ${SOURCES})
  # Get the filename without the extension
  get_filename_component(filename_we ${source} NAME_WE)
  # Get the parent directory of the source file
  get_filename_component(parent_dir ${source} DIRECTORY)
  string(REPLACE "${CMAKE_SOURCE_DIR}/src/" "" parent_dir_rel ${parent_dir})
  # Create a unique target name
  set(target_name "${parent_dir_rel}_${filename_we}")
  # Replace any slashes with underscores
  string(REPLACE "/" "_" target_name ${target_name})
  # Create an executable target
  add_executable(${target_name} ${source})
endforeach()