file(GLOB_RECURSE SIM_SOURCES
    "src/*.cpp"
    "src/*.c"
    "src/*.h")  

file(GLOB_RECURSE SIM_HEADERS
    "include/*.h"
    "include/*.hpp") 

add_library(Simulation STATIC ${SIM_SOURCES} ${SIM_HEADERS})
  
target_include_directories(Simulation PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_SOURCE_DIR}/dependencies/glm)

target_link_libraries(Simulation PUBLIC spdlog)

target_compile_features(Simulation PUBLIC cxx_std_17)