cmake_minimum_required(VERSION 3.7)
project(ppgl)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES ppgl.h Window.cpp Window.h PPGL_Exception.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

#Link to GLFW library
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME}  ${GLFW_STATIC_LIBRARIES})

#Link to Vulkan library
find_package(Vulkan REQUIRED)
target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_XLIB_KHR)
target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
