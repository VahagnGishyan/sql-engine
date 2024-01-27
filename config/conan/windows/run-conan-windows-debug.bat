
conan install . --build=missing --profile:build=config/conan/windows/windows-debug-x64 --profile:host=config/conan/windows/windows-debug-x64
cmake --preset conan-default
cmake --build build
