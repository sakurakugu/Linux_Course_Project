cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(FractalDragon VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# 包含头文件目录
include_directories(cpp)

# 收集所有源文件
file(GLOB SOURCES 
    "cpp/*.cpp"
)

# 收集所有头文件
file(GLOB HEADERS 
    "cpp/*.h"
)

# 创建可执行文件
add_executable(
    ${PROJECT_NAME}
    ${SOURCES} 
    ${HEADERS}
)

# 链接数学库
target_link_libraries(${PROJECT_NAME} m)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# 打印构建信息
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")