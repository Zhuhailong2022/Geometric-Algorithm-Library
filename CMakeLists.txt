cmake_minimum_required(VERSION 3.10)
project(DynamicLibrary)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 查找所有源文件
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# 设置库和可执行文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 创建动态库
add_library(dynamicLibrary SHARED ${SRC_LIST})

# 创建可执行文件
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main dynamicLibrary sfml-graphics sfml-window sfml-system)

# cmake_minimum_required(VERSION 3.10)
# project(DynamicLibrary)

# # 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 11)

# # 包含头文件路径
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# # 查找所有源文件
# file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/polygonArea.cpp)

# # 设置可执行文件输出路径
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# # 创建可执行文件
# add_executable(main ${SRC_LIST})
