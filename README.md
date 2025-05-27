# Overview

As I’ve been digging deeper into systems programming, I wanted to get practical with C++ and see how it handles things like memory, performance, and object-oriented design. Coming from higher-level languages, I was especially interested in the control C++ gives you and what it costs in complexity.

This to-do list manager is a simple console app that let me explore core C++ features like class design, file I/O, and RAII. It supports adding, viewing, completing, and removing tasks, with everything saved between sessions. Working on it helped me understand how C++ manages resources without a garbage collector, and gave me a real feel for separating code into headers and source files, and using the STL effectively.


[Software Demo Video](http://youtube.link.goes.here)

# Development Environment

Language: C++

IDE: CLion (Apple Clang compiler)

Compiler: Apple Clang 17.0.0

Libraries: <iostream>, <string>, <vector>, <fstream>, <iomanip>, <stdexcept>, <chrono>, <ctime>, <limits>

# Useful Websites

- [C++ standard library functions and language features](https://en.cppreference.com/)
- [Tutorials covering modern C++ practices and common pitfalls](https://www.learncpp.com/)
- [Stack Overflow C++ Tag ](https://stackoverflow.com/questions/tagged/c%2b%2b)
- [Modern C++ best practices from the language creators](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Online tool for examining compiler output and optimization behavior](https://godbolt.org/)
- [Language references and STL documentation](https://cplusplus.com/)
- [Useful for understanding class design and exception handling](https://www.geeksforgeeks.org/cpp-programming-language/)

# Future Work

- Add priority levels and due dates to tasks with automatic sorting capabilities
- Implement search and filter functionality to handle larger task lists efficiently
- Create a configuration system for customizable file paths and display preferences
- Add data validation and error recovery for corrupted save files
- Implement task categories/tags with color-coded console output
- Add unit tests using a framework like Google Test to ensure code reliability
- Optimize file I/O operations for better performance with large datasets
- Create a cross-platform build system using CMake for easier distribution