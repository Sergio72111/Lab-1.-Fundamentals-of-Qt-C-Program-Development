# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(OopSingleFileCalculator VERSION 1.1)

# Установка стандарта C++17 (современный и рекомендуемый)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Список исходных файлов. Теперь это только один файл.
set(SOURCE_FILES
    calculator.cpp
)

# Создание исполняемого файла с именем Calculator
add_executable(Calculator ${SOURCE_FILES})

# Линковка с математической библиотекой 'm'. 
# Это необходимо для функций std::isnan() и std::numeric_limits на некоторых платформах (например, Linux/MinGW).
target_link_libraries(Calculator PRIVATE m)