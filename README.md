# Dictionary

## Tools
- C++17 compiler (GCC, MinGW, Visual Studio, ...)
- CMake
- Conan

## Build

Create build folder
```bash
mkdir build
cd build
```

Install dependencies with **Conan**
Launch build with **CMake** executable
```bash
conan install .. --build=missing -s compiler.libcxx=libstdc++11
cmake ..
cmake --build .
```

## Tests

Into **build** folder
```bash
./bin/unit-tests # Linux & Mac
"bin\unit-tests" # Windows
```
