cmake_minimum_required(VERSION 3.17)
project(FEUP_Projeto_CAL)

set(CMAKE_CXX_STANDARD 14)

add_executable(FEUP_Projeto_CAL main.cpp graph/Graph.cpp graph/Graph.h graph/Vertex.cpp graph/Vertex.h graph/Edge.cpp graph/Edge.h utils/Position.cpp utils/Position.h utils/Time.cpp utils/Time.h)