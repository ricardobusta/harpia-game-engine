#
# Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
#

cmake_minimum_required(VERSION 3.22)
project(Harpia LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(Harpia STATIC Core.cpp)
target_include_directories(Harpia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})