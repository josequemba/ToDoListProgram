#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include "Task.h"

class TodoList {
private:
    std::vector<Task> tasks;
    int nextTaskId;

public:
    // Constructor
    TodoList();

    // Methods
    void addTask(const std::string& description);
    bool removeTask(int id);
    bool markTaskAsCompleted(int id);
    std::vector<Task> getAllTasks() const;
    Task* getTaskById(int id);
    void clearAllTasks();
    int getTaskCount() const;
    std::vector<Task> getCompletedTasks() const;
    std::vector<Task> getPendingTasks() const;
    void setTasks(const std::vector<Task>& tasks);
};

#endif // TODOLIST_H