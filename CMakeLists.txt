cmake_minimum_required(VERSION 3.16)

# Variables
set(DEV_DISTRIBUTED TRUE) # Set to TRUE if the project files should get distributed to the project dirs

# Project
project("Fluidify")

# Subdirectories
set(GENERATOR_PATH ${CMAKE_BINARY_DIR}) 

if(${DEV_DISTRIBUTED})
    set(GENERATOR_PATH ${CMAKE_SOURCE_DIR})
endif()  

add_subdirectory("Fluidify" ${GENERATOR_PATH}/Fluidify)

# Visual Studio Startup Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Fluidify)