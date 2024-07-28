set(CMAKE_PREFIX_PATH C:/Qt/6.7.2/msvc2019_64/lib/cmake/Qt6)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        OpenGLWidgets
)
qt_standard_project_setup()

file(GLOB_RECURSE PROJECT_SOURCES
    "src/*.cpp"
    "src/*.c")  

file(GLOB_RECURSE PROJECT_HEADERS
    "src/*.h"
    "src/*.hpp"
    "src/*.ui") 

qt_add_executable(Fluidify ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(Fluidify PUBLIC src/)

set_target_properties(Fluidify
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(Fluidify
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
)

target_link_libraries(Fluidify
    PUBLIC
        Simulation
        GLWrapper
)
