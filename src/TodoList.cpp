#include "TodoList.h"
#include <algorithm>

// Constructor: Start task IDs at 1
TodoList::TodoList() : nextTaskId(1) {}

// Adds a new task with a unique ID
void TodoList::addTask(const std::string& description) {
    Task newTask(nextTaskId, description);
    tasks.push_back(newTask);
    nextTaskId++; // Prepare for the next task
}

// Removes a task by ID if it exists
bool TodoList::removeTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [id](const Task& task) { return task.getId() == id; });

    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }

    return false;
}

// Marks a task as completed based on its ID
bool TodoList::markTaskAsCompleted(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.markAsCompleted();
            return true;
        }
    }
    return false;
}

// Returns a copy of all tasks
std::vector<Task> TodoList::getAllTasks() const {
    return tasks;
}

// Finds a task by ID and returns a pointer to it (nullptr if not found)
Task* TodoList::getTaskById(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            return &task;
        }
    }
    return nullptr;
}

// Clears every task from the list and resets the ID counter
void TodoList::clearAllTasks() {
    tasks.clear();
    nextTaskId = 1;
}

// Returns how many tasks are currently in the list
int TodoList::getTaskCount() const {
    return tasks.size();
}

// Returns only the completed tasks
std::vector<Task> TodoList::getCompletedTasks() const {
    std::vector<Task> completedTasks;

    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            completedTasks.push_back(task);
        }
    }

    return completedTasks;
}

// Returns tasks that haven't been completed yet
std::vector<Task> TodoList::getPendingTasks() const {
    std::vector<Task> pendingTasks;

    for (const auto& task : tasks) {
        if (!task.isCompleted()) {
            pendingTasks.push_back(task);
        }
    }

    return pendingTasks;
}

// Loads a list of tasks (e.g. from file) and updates the nextTaskId
void TodoList::setTasks(const std::vector<Task>& tasks) {
    this->tasks = tasks;

    // Make sure future task IDs are unique
    nextTaskId = 1;
    for (const auto& task : tasks) {
        if (task.getId() >= nextTaskId) {
            nextTaskId = task.getId() + 1;
        }
    }
}