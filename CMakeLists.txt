cmake_minimum_required(VERSION 3.16)

project(lws-test)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address -lcap)

add_subdirectory(apps/server)
