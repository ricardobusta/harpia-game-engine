#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(GAME LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(GAME Main.cpp)
target_link_libraries(GAME PRIVATE ENGINE)