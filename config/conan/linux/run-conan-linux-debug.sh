conan install . --output-folder=build --build=missing --profile:build=config/conan/linux/linux-debug-x64 --profile:host=config/conan/linux/linux-debug-x64
# cmake --preset conan-debug
cmake --build build