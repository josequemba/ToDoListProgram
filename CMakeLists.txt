cmake_minimum_required(VERSION 3.16)
project(ToDoListManager_)

# Use the latest available working standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files
add_executable(ToDoListManager_
        src/main.cpp
        src/Task.cpp
        src/TodoList.cpp
        src/FileManager.cpp
)