cmake_minimum_required(VERSION 3.16)
project(ppgl_Test)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#Link to PPGL library
include(FindPkgConfig)
find_package(PPGL REQUIRED)
include_directories(${PPGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${PPGL_LIBRARY})

#Link to GLFW library
pkg_search_module(GLFW REQUIRED glfw3)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME}  ${GLFW_STATIC_LIBRARIES})

#Link to Vulkan library
find_package(Vulkan REQUIRED)
target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_XLIB_KHR)
target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)