conan install . --output-folder=build --build=missing --profile:build=config/conan/linux-debug-x64 --profile:host=config/conan/linux-debug-x64
# cmake --preset conan-debug
cmake --build build