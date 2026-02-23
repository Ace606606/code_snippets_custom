# Code Snippets Custom Template

Базовый шаблон для C++ проектов с поддержкой логгера, таймера и Unit-тестов.

## Options
- DCSC_BUILD_TESTS=ON/OFF: Build tests (default ON).
- DCSC_BUILD_SPDLOG=ON/OFF: Использовать spdlog или форматный вывод через fmt (default ON).
- DCSC_BUILD_EXTERNAL_DEPS=ON/OFF: Разрешить скачивание зависимостей из сети
- DFETCHCONTENT_BASE_DIR=~/cmake_dependencies: Установить зависимости отдельно

## Build
```Bash
# Configure
cmake -B build-debug -DCSC_BUILD_TESTS=ON -DCSC_BUILD_EXAMPLES=ON

# Build
cmake --build build-debug -j$(nproc)

# Run test
cd build-debug && ctest --output-on-failure
