#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include "Task.h"

class TodoList {
private:
    std::vector<Task> tasks;     // Stores all the tasks in the list
    int nextTaskId;              // Keeps track of the next available ID to assign

public:
    // Constructor
    TodoList();  // Sets up the to-do list (likely sets nextTaskId to 1 or 0)

    // Adds a new task with the given description
    void addTask(const std::string& description);

    // Removes a task by ID; returns true if successful
    bool removeTask(int id);

    // Marks a task as completed by ID; returns true if it exists and was updated
    bool markTaskAsCompleted(int id);

    // Returns a copy of all tasks (both completed and pending)
    std::vector<Task> getAllTasks() const;

    // Returns a pointer to a task by ID, or nullptr if it’s not found
    Task* getTaskById(int id);

    // Clears the entire task list
    void clearAllTasks();

    // Returns the total number of tasks
    int getTaskCount() const;

    // Returns only the tasks that are marked as completed
    std::vector<Task> getCompletedTasks() const;

    // Returns only the tasks that are still pending
    std::vector<Task> getPendingTasks() const;

    // Replaces the current task list with a new one (useful when loading from file)
    void setTasks(const std::vector<Task>& tasks);
};

#endif // TODOLIST_H