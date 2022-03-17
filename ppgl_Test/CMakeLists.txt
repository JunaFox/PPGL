cmake_minimum_required(VERSION 3.16)
project(ppgl_Test)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#Link to PPGL library
find_package(PPGL REQUIRED)
message(STATUS "O: ${PPGL_LIBRARY}")
include_directories(${PPGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${PPGL_LIBRARY})

#Link to GLFW library
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

#Link to Vulkan library
find_package(Vulkan REQUIRED)
target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)