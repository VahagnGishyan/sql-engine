conan install . --output-folder=build --build=missing --profile:build=config/conan/windows-debug-x64 --profile:host=config/conan/windows-debug-x64
cmake --preset conan-default
cmake --build build