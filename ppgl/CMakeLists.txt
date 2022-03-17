cmake_minimum_required(VERSION 3.7)
project(ppgl)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES ppgl.h Window.cpp Window.h PPGL_Exception.h Vulkan.cpp Vulkan.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#Link to GLFW library
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

#Link to Vulkan library
find_package(Vulkan REQUIRED)
target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
