cmake_minimum_required(VERSION 3.17)
project(FEUP_Projeto_CAL)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

add_executable(FEUP_Projeto_CAL main.cpp graph/Graph.cpp graph/Graph.h graph/Vertex.cpp graph/Vertex.h graph/Edge.cpp graph/Edge.h utils/Position.cpp utils/Position.h utils/Time.cpp utils/Time.h utils/GraphBuilder.cpp utils/GraphBuilder.h bakery/Van.cpp bakery/Van.h bakery/Client.cpp bakery/Client.h bakery/Bakery.cpp bakery/Bakery.h bakery/Interface.cpp bakery/Interface.h)

target_link_libraries(FEUP_Projeto_CAL graphviewer)