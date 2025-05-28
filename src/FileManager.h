#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "Task.h"

// FileManager handles reading and writing tasks to a file
class FileManager {
private:
    std::string filePath; // Path to the tasks file

public:
    // Constructor with a default path, makes it easy to use out-of-the-box
    FileManager(const std::string& filePath = "data/tasks.txt");

    // Saves all tasks to file — returns true if successful
    bool saveTasks(const std::vector<Task>& tasks);

    // Loads tasks from file — returns the list (empty if file not found or unreadable)
    std::vector<Task> loadTasks();

    // Utility to check if the file exists
    bool fileExists() const;
};

#endif // FILE_MANAGER_H