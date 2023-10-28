conan install . --output-folder=build --build=missing --profile:build=.conan/linux-debug-x64 --profile:host=.conan/linux-debug-x64
cmake --preset conan-debug
cmake --build build