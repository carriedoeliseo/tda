cmake_minimum_required(VERSION 3.29)
project(practicas)

set(CMAKE_CXX_STANDARD 14)

add_executable(aristapuente practica4/dfs_aristaspuente.cpp)
add_executable(distanicamax practica2/dq_distanciamax.cpp)
add_executable(kn practica4/agm_kn.cpp)
add_executable(anchobanda practica4/agm_anchobanda.cpp)

