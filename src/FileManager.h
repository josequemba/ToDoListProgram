#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "Task.h"

class FileManager {
private:
    std::string filePath;

public:
    // Constructor
    FileManager(const std::string& filePath = "data/tasks.txt");

    // Methods
    bool saveTasks(const std::vector<Task>& tasks);
    std::vector<Task> loadTasks();
    bool fileExists() const;
};

#endif // FILE_MANAGER_H