# Fluidity
A realtime fluid simulator
## Build with CMake
This project uses CMake for project configuration. Run the following steps to build the project:
```sh
git clone ... --recursive # To clone submodules!
cd ...
mkdir build
cd build
cmake ..
cmake --build .
```
**IMPORTANT**: You must bring your own Qt installation, set the installation path inside ```./qt_ver.cmake```.
