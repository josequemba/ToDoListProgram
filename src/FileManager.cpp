#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>

// Constructor
FileManager::FileManager(const std::string& filePath) : filePath(filePath) {
    try {
        // Create the data directory if it doesn't exist
        std::string dirPath = "data";
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directory(dirPath);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        throw std::runtime_error("Failed to initialize file manager: " + std::string(e.what()));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Failed to initialize file manager: " + std::string(e.what()));
    }
}

// Methods
bool FileManager::saveTasks(const std::vector<Task>& tasks) {
    try {
        std::ofstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
            return false;
        }

        for (const auto& task : tasks) {
            file << task.toString() << std::endl;

            if (file.fail()) {
                std::cerr << "Error: Failed to write task to file." << std::endl;
                file.close();
                return false;
            }
        }

        file.close();
        if (file.fail()) {
            std::cerr << "Error: Failed to close the file properly." << std::endl;
            return false;
        }

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving tasks: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Task> FileManager::loadTasks() {
    std::vector<Task> tasks;

    try {
        if (!fileExists()) {
            std::cout << "Note: No existing task file found." << std::endl;
            return tasks;
        }

        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Warning: Could not open file for reading: " << filePath << std::endl;
            return tasks;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                try {
                    Task task = Task::fromString(line);
                    tasks.push_back(task);
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing task: " << e.what() << std::endl;
                    std::cerr << "Skipping malformed task entry." << std::endl;
                }
            }
        }

        if (file.bad()) {
            std::cerr << "Error: Failed reading from file." << std::endl;
        }

        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
    }

    return tasks;
}

bool FileManager::fileExists() const {
    try {
        return std::filesystem::exists(filePath);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error checking file existence: " << e.what() << std::endl;
        return false;
    }
}