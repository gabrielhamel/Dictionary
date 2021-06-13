# Dictionary

## Tools
- GCC
- CMake

## Build

Create build folder
```bash
mkdir build
cd build
```

Launch build with cmake executable
```bash
conan install .. --build=missing -s compiler.libcxx=libstdc++11
cmake ..
cmake --build .
```
