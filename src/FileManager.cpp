#include "FileManager.h"
#include <fstream>      // For file input/output operations
#include <iostream>     // For console output (cerr, cout)
#include <filesystem>   // For filesystem operations like checking and creating directories
#include <stdexcept>    // For exception handling (std::runtime_error, std::invalid_argument, etc.)

// Constructor
FileManager::FileManager(const std::string& filePath) : filePath(filePath) {
    try {
        // Attempt to ensure the "data" directory exists before using the file
        std::string dirPath = "data";
        if (!std::filesystem::exists(dirPath)) {
            // If not, create it
            std::filesystem::create_directory(dirPath);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        // Catch and report any filesystem-specific errors
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        throw std::runtime_error("Failed to initialize file manager: " + std::string(e.what()));
    } catch (const std::exception& e) {
        // Catch and report any other exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Failed to initialize file manager: " + std::string(e.what()));
    }
}

// Methods
bool FileManager::saveTasks(const std::vector<Task>& tasks) {
    try {
        // Open the file for writing (overwrites existing content)
        std::ofstream file(filePath);

        if (!file.is_open()) {
            // If opening fails, print an error and return false
            std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
            return false;
        }

        // Write each task as a line in the file
        for (const auto& task : tasks) {
            file << task.toString() << std::endl;

            // Check if writing failed at any point
            if (file.fail()) {
                std::cerr << "Error: Failed to write task to file." << std::endl;
                file.close();
                return false;
            }
        }

        // Close the file after writing
        file.close();
        // Check if the close operation failed
        if (file.fail()) {
            std::cerr << "Error: Failed to close the file properly." << std::endl;
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        // Catch and report any exceptions during the save process
        std::cerr << "Error saving tasks: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Task> FileManager::loadTasks() {
    std::vector<Task> tasks;

    try {
        // If the file doesn't exist, notify the user and return an empty list
        if (!fileExists()) {
            std::cout << "Note: No existing task file found." << std::endl;
            return tasks;
        }

        // Open the file for reading
        std::ifstream file(filePath);

        if (!file.is_open()) {
            // If opening fails, notify and return empty list
            std::cerr << "Warning: Could not open file for reading: " << filePath << std::endl;
            return tasks;
        }

        std::string line;
        // Read the file line by line
        while (std::getline(file, line)) {
            if (!line.empty()) {
                try {
                    // Attempt to parse each line into a Task object
                    Task task = Task::fromString(line);
                    tasks.push_back(task);
                } catch (const std::exception& e) {
                    // If parsing fails, report the error and skip the line
                    std::cerr << "Error parsing task: " << e.what() << std::endl;
                    std::cerr << "Skipping malformed task entry." << std::endl;
                }
            }
        }

        // Check if an error occurred while reading
        if (file.bad()) {
            std::cerr << "Error: Failed reading from file." << std::endl;
        }

        // Close the file after reading
        file.close();
    } catch (const std::exception& e) {
        // Catch and report any errors during the load process
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
    }

    return tasks;
}

bool FileManager::fileExists() const {
    try {
        // Check if the file exists at the given path
        return std::filesystem::exists(filePath);
    } catch (const std::filesystem::filesystem_error& e) {
        // If checking fails (e.g., permission issue), report it
        std::cerr << "Filesystem error checking file existence: " << e.what() << std::endl;
        return false;
    }
}